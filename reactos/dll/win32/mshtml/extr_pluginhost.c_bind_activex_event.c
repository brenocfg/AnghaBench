#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_17__ {int /*<<< orphan*/ * typeinfo; } ;
struct TYPE_16__ {TYPE_1__* plugin_host; } ;
struct TYPE_15__ {TYPE_5__* sink; int /*<<< orphan*/  plugin_unk; } ;
typedef  TYPE_1__ PluginHost ;
typedef  int /*<<< orphan*/  ITypeInfo ;
typedef  int /*<<< orphan*/  IProvideClassInfo ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  TYPE_2__ HTMLPluginContainer ;
typedef  int /*<<< orphan*/  HTMLDocumentNode ;
typedef  TYPE_1__* HRESULT ;
typedef  int /*<<< orphan*/  DISPID ;

/* Variables and functions */
 scalar_t__ FAILED (TYPE_1__*) ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  IID_IProvideClassInfo ; 
 TYPE_1__* IProvideClassInfo_GetClassInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IProvideClassInfo_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITypeInfo_AddRef (int /*<<< orphan*/ *) ; 
 TYPE_1__* ITypeInfo_GetIDsOfNames (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITypeInfo_Release (int /*<<< orphan*/ *) ; 
 TYPE_1__* IUnknown_QueryInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  add_sink_handler (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_5__* create_event_sink (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_eventiface_info (TYPE_2__*,int /*<<< orphan*/ *) ; 

void bind_activex_event(HTMLDocumentNode *doc, HTMLPluginContainer *plugin_container, WCHAR *event, IDispatch *disp)
{
    PluginHost *plugin_host = plugin_container->plugin_host;
    ITypeInfo *class_info, *source_info;
    DISPID id;
    HRESULT hres;

    TRACE("(%p %p %s %p)\n", doc, plugin_host, debugstr_w(event), disp);

    if(!plugin_host || !plugin_host->plugin_unk) {
        WARN("detached element %p\n", plugin_host);
        return;
    }

    if(plugin_host->sink) {
        source_info = plugin_host->sink->typeinfo;
        ITypeInfo_AddRef(source_info);
    }else {
        IProvideClassInfo *provide_ci;

        hres = IUnknown_QueryInterface(plugin_host->plugin_unk, &IID_IProvideClassInfo, (void**)&provide_ci);
        if(FAILED(hres)) {
            FIXME("No IProvideClassInfo, try GetTypeInfo?\n");
            return;
        }

        hres = IProvideClassInfo_GetClassInfo(provide_ci, &class_info);
        IProvideClassInfo_Release(provide_ci);
        if(FAILED(hres) || !class_info) {
            WARN("GetClassInfo failed: %08x\n", hres);
            return;
        }

        source_info = get_eventiface_info(plugin_container, class_info);
        ITypeInfo_Release(class_info);
        if(!source_info)
            return;
    }

    hres = ITypeInfo_GetIDsOfNames(source_info, &event, 1, &id);
    if(FAILED(hres))
        WARN("Could not get disp id: %08x\n", hres);
    else if(!plugin_host->sink)
        plugin_host->sink = create_event_sink(plugin_host, source_info);

    ITypeInfo_Release(source_info);
    if(FAILED(hres) || !plugin_host->sink)
        return;

    add_sink_handler(plugin_host->sink, id, disp);
}