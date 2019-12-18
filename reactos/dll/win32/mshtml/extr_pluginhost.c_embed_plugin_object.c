#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ ip_object; int /*<<< orphan*/  hwnd; int /*<<< orphan*/  IOleClientSite_iface; int /*<<< orphan*/  plugin_unk; } ;
typedef  int /*<<< orphan*/  RECT ;
typedef  TYPE_1__ PluginHost ;
typedef  int /*<<< orphan*/  IOleObject ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  IID_IOleObject ; 
 int /*<<< orphan*/  IOleInPlaceObject_GetWindow (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IOleObject_DoVerb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IOleObject_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IUnknown_QueryInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  OLEIVERB_INPLACEACTIVATE ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_pos_rect (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void embed_plugin_object(PluginHost *host)
{
    IOleObject *ole_obj;
    RECT rect;
    HRESULT hres;

    hres = IUnknown_QueryInterface(host->plugin_unk, &IID_IOleObject, (void**)&ole_obj);
    if(FAILED(hres)) {
        FIXME("Plugin does not support IOleObject\n");
        return;
    }

    get_pos_rect(host, &rect);
    hres = IOleObject_DoVerb(ole_obj, OLEIVERB_INPLACEACTIVATE, NULL, &host->IOleClientSite_iface, 0, host->hwnd, &rect);
    IOleObject_Release(ole_obj);
    if(FAILED(hres))
        WARN("DoVerb failed: %08x\n", hres);

    if(host->ip_object) {
        HWND hwnd;

        hres = IOleInPlaceObject_GetWindow(host->ip_object, &hwnd);
        if(SUCCEEDED(hres))
            TRACE("hwnd %p\n", hwnd);
    }
}