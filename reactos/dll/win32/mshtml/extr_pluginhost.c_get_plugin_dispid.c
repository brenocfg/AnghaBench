#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_5__ {size_t props_len; scalar_t__* props; int props_size; TYPE_1__* plugin_host; } ;
struct TYPE_4__ {int /*<<< orphan*/ * disp; } ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  TYPE_2__ HTMLPluginContainer ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  size_t DWORD ;
typedef  scalar_t__ DISPID ;

/* Variables and functions */
 int /*<<< orphan*/  DISP_E_UNKNOWNNAME ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDispatch_GetIDsOfNames (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  IID_NULL ; 
 scalar_t__ MSHTML_DISPID_CUSTOM_MIN ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ *) ; 
 scalar_t__* heap_alloc (int) ; 
 scalar_t__* heap_realloc (scalar_t__*,int) ; 

HRESULT get_plugin_dispid(HTMLPluginContainer *plugin_container, WCHAR *name, DISPID *ret)
{
    IDispatch *disp;
    DISPID id;
    DWORD i;
    HRESULT hres;

    if(!plugin_container->plugin_host) {
        WARN("no plugin host\n");
        return DISP_E_UNKNOWNNAME;
    }

    disp = plugin_container->plugin_host->disp;
    if(!disp)
        return DISP_E_UNKNOWNNAME;

    hres = IDispatch_GetIDsOfNames(disp, &IID_NULL, &name, 1, 0, &id);
    if(FAILED(hres)) {
        TRACE("no prop %s\n", debugstr_w(name));
        return DISP_E_UNKNOWNNAME;
    }

    for(i=0; i < plugin_container->props_len; i++) {
        if(id == plugin_container->props[i]) {
            *ret = MSHTML_DISPID_CUSTOM_MIN+i;
            return S_OK;
        }
    }

    if(!plugin_container->props) {
        plugin_container->props = heap_alloc(8*sizeof(DISPID));
        if(!plugin_container->props)
            return E_OUTOFMEMORY;
        plugin_container->props_size = 8;
    }else if(plugin_container->props_len == plugin_container->props_size) {
        DISPID *new_props;

        new_props = heap_realloc(plugin_container->props, plugin_container->props_size*2*sizeof(DISPID));
        if(!new_props)
            return E_OUTOFMEMORY;

        plugin_container->props = new_props;
        plugin_container->props_size *= 2;
    }

    plugin_container->props[plugin_container->props_len] = id;
    *ret = MSHTML_DISPID_CUSTOM_MIN+plugin_container->props_len;
    plugin_container->props_len++;
    return S_OK;
}