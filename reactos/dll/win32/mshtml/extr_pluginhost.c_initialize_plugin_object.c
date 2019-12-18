#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  control ;
typedef  int /*<<< orphan*/  container ;
struct TYPE_11__ {int /*<<< orphan*/  plugin_unk; int /*<<< orphan*/ * disp; int /*<<< orphan*/  IAdviseSinkEx_iface; int /*<<< orphan*/  IOleClientSite_iface; int /*<<< orphan*/  IPropertyNotifySink_iface; } ;
struct TYPE_10__ {int member_0; int dwAmbientFlags; int /*<<< orphan*/ * pPropertyNotifySink; int /*<<< orphan*/ * pAdviseSink; int /*<<< orphan*/ * pClientSite; } ;
struct TYPE_9__ {int member_0; } ;
typedef  TYPE_1__ QACONTROL ;
typedef  TYPE_2__ QACONTAINER ;
typedef  TYPE_3__ PluginHost ;
typedef  int /*<<< orphan*/  IViewObjectEx ;
typedef  int /*<<< orphan*/  IQuickActivate ;
typedef  int /*<<< orphan*/  IOleObject ;
typedef  int /*<<< orphan*/  IOleCommandTarget ;
typedef  int /*<<< orphan*/  IDispatchEx ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  int /*<<< orphan*/  IClientSecurity ;
typedef  int /*<<< orphan*/  IAdviseSink ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  DVASPECT_CONTENT ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*,...) ; 
 int /*<<< orphan*/  IClientSecurity_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IClientSecurity ; 
 int /*<<< orphan*/  IID_IDispatch ; 
 int /*<<< orphan*/  IID_IDispatchEx ; 
 int /*<<< orphan*/  IID_IOleCommandTarget ; 
 int /*<<< orphan*/  IID_IOleObject ; 
 int /*<<< orphan*/  IID_IQuickActivate ; 
 int /*<<< orphan*/  IID_IViewObjectEx ; 
 int /*<<< orphan*/  IOleCommandTarget_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IOleObject_GetMiscStatus (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IOleObject_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IOleObject_SetClientSite (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IQuickActivate_QuickActivate (int /*<<< orphan*/ *,TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  IQuickActivate_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IUnknown_QueryInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IViewObjectEx_GetViewStatus (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IViewObjectEx_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IViewObjectEx_SetAdvise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int QACONTAINER_MESSAGEREFLECT ; 
 int QACONTAINER_SUPPORTSMNEMONICS ; 
 int QACONTAINER_USERMODE ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_plugin (TYPE_3__*) ; 
 int /*<<< orphan*/  update_readystate (TYPE_3__*) ; 

__attribute__((used)) static void initialize_plugin_object(PluginHost *host)
{
    IClientSecurity *client_security;
    IQuickActivate *quick_activate;
    IOleObject *ole_obj = NULL;
    IOleCommandTarget *cmdtrg;
    IViewObjectEx *view_obj;
    IDispatchEx *dispex;
    IDispatch *disp;
    HRESULT hres;

    /* Note native calls QI on plugin for an undocumented IID and CLSID_HTMLDocument */

    /* FIXME: call FreezeEvents(TRUE) */

    hres = IUnknown_QueryInterface(host->plugin_unk, &IID_IClientSecurity, (void**)&client_security);
    if(SUCCEEDED(hres)) {
        FIXME("Handle IClientSecurity\n");
        IClientSecurity_Release(client_security);
        return;
    }

    hres = IUnknown_QueryInterface(host->plugin_unk, &IID_IQuickActivate, (void**)&quick_activate);
    if(SUCCEEDED(hres)) {
        QACONTAINER container = {sizeof(container)};
        QACONTROL control = {sizeof(control)};

        TRACE("Using IQuickActivate\n");

        container.pClientSite = &host->IOleClientSite_iface;
        container.dwAmbientFlags = QACONTAINER_SUPPORTSMNEMONICS|QACONTAINER_MESSAGEREFLECT|QACONTAINER_USERMODE;
        container.pAdviseSink = &host->IAdviseSinkEx_iface;
        container.pPropertyNotifySink = &host->IPropertyNotifySink_iface;

        hres = IQuickActivate_QuickActivate(quick_activate, &container, &control);
        IQuickActivate_Release(quick_activate);
        if(FAILED(hres))
            FIXME("QuickActivate failed: %08x\n", hres);
    }else {
        DWORD status = 0;

        hres = IUnknown_QueryInterface(host->plugin_unk, &IID_IOleObject, (void**)&ole_obj);
        if(SUCCEEDED(hres)) {
            hres = IOleObject_GetMiscStatus(ole_obj, DVASPECT_CONTENT, &status);
            TRACE("GetMiscStatus returned %08x %x\n", hres, status);

            hres = IOleObject_SetClientSite(ole_obj, &host->IOleClientSite_iface);
            IOleObject_Release(ole_obj);
            if(FAILED(hres)) {
                FIXME("SetClientSite failed: %08x\n", hres);
                return;
            }
        }else {
            TRACE("Plugin does not support IOleObject\n");
        }
    }

    load_plugin(host);

    if(ole_obj) {
        hres = IUnknown_QueryInterface(host->plugin_unk, &IID_IViewObjectEx, (void**)&view_obj);
        if(SUCCEEDED(hres)) {
            DWORD view_status = 0;

            hres = IViewObjectEx_SetAdvise(view_obj, DVASPECT_CONTENT, 0, (IAdviseSink*)&host->IAdviseSinkEx_iface);
            if(FAILED(hres))
                WARN("SetAdvise failed: %08x\n", hres);

            hres = IViewObjectEx_GetViewStatus(view_obj, &view_status);
            IViewObjectEx_Release(view_obj);
            TRACE("GetViewStatus returned %08x %x\n", hres, view_status);
        }
    }

    update_readystate(host);

    /* NOTE: Native QIs for IActiveScript, an undocumented IID, IOleControl and IRunnableObject */

    hres = IUnknown_QueryInterface(host->plugin_unk, &IID_IDispatchEx, (void**)&dispex);
    if(SUCCEEDED(hres)) {
        FIXME("Use IDispatchEx\n");
        host->disp = (IDispatch*)dispex;
    }else {
        hres = IUnknown_QueryInterface(host->plugin_unk, &IID_IDispatch, (void**)&disp);
        if(SUCCEEDED(hres))
            host->disp = disp;
        else
            TRACE("no IDispatch iface\n");
    }

    hres = IUnknown_QueryInterface(host->plugin_unk, &IID_IOleCommandTarget, (void**)&cmdtrg);
    if(SUCCEEDED(hres)) {
        FIXME("Use IOleCommandTarget\n");
        IOleCommandTarget_Release(cmdtrg);
    }
}