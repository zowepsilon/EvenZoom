#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/EditorUI.hpp>

class $modify(MyEditorUI, EditorUI) {
    struct Fields {
        double zoomStep;
        bool limitZoom;
        double minZoom;
        double maxZoom;
    };

    bool init(LevelEditorLayer* editorLayer) {
        if (!EditorUI::init(editorLayer)) return false;
        
        m_fields->zoomStep = Mod::get()->getSettingValue<double>("zoom-step");
        m_fields->limitZoom = Mod::get()->getSettingValue<bool>("limit-zoom");
        m_fields->minZoom = Mod::get()->getSettingValue<double>("min-zoom");
        m_fields->maxZoom = Mod::get()->getSettingValue<double>("max-zoom");

        return true;
    }
    

    void zoomIn(CCObject* sender) {
        auto zoom = m_editorLayer->m_objectLayer->getScale();
        float newZoom = zoom*m_fields->zoomStep;

        if (m_fields->limitZoom && (zoom < m_fields->minZoom || newZoom < m_fields->minZoom || newZoom > m_fields->maxZoom)) return;
        EditorUI::updateZoom(newZoom);
    }

    void zoomOut(CCObject* sender) {
        auto zoom = m_editorLayer->m_objectLayer->getScale();
        float newZoom = zoom/m_fields->zoomStep;

        if (m_fields->limitZoom && (zoom > m_fields->maxZoom || newZoom < m_fields->minZoom || newZoom > m_fields->maxZoom)) return;
        EditorUI::updateZoom(newZoom);
    }
};
