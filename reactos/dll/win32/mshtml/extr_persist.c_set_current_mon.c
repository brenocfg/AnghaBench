#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_8__ {TYPE_2__* window; } ;
struct TYPE_10__ {TYPE_1__ basedoc; } ;
struct TYPE_9__ {int load_flags; int /*<<< orphan*/  url; int /*<<< orphan*/ * mon; TYPE_7__* doc_obj; } ;
typedef  int /*<<< orphan*/  IUriContainer ;
typedef  int /*<<< orphan*/  IUri ;
typedef  int /*<<< orphan*/  IMoniker ;
typedef  TYPE_2__ HTMLOuterWindow ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;

/* Variables and functions */
 int BINDING_REFRESH ; 
 int BINDING_REPLACE ; 
 int /*<<< orphan*/  CoTaskMemFree (int /*<<< orphan*/ *) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IUriContainer ; 
 int /*<<< orphan*/  IMoniker_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IMoniker_GetDisplayName (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IMoniker_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IMoniker_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IUriContainer_GetIUri (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IUriContainer_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IUri_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SCRIPTMODE_ACTIVESCRIPT ; 
 int /*<<< orphan*/  SCRIPTMODE_GECKO ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  SysAllocString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_uri (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  notify_travellog_update (TYPE_7__*) ; 
 int /*<<< orphan*/  set_current_uri (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_script_mode (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ use_gecko_script (TYPE_2__*) ; 

void set_current_mon(HTMLOuterWindow *This, IMoniker *mon, DWORD flags)
{
    IUriContainer *uri_container;
    IUri *uri = NULL;
    HRESULT hres;

    if(This->mon) {
        if(This->doc_obj && !(flags & (BINDING_REPLACE|BINDING_REFRESH))) {
            if(This == This->doc_obj->basedoc.window)
                notify_travellog_update(This->doc_obj);
            else
                TRACE("Skipping travellog update for frame navigation.\n");
        }
        IMoniker_Release(This->mon);
        This->mon = NULL;
    }

    This->load_flags = flags;
    if(!mon)
        return;

    IMoniker_AddRef(mon);
    This->mon = mon;

    hres = IMoniker_QueryInterface(mon, &IID_IUriContainer, (void**)&uri_container);
    if(SUCCEEDED(hres)) {
        hres = IUriContainer_GetIUri(uri_container, &uri);
        IUriContainer_Release(uri_container);
        if(hres != S_OK) {
            WARN("GetIUri failed: %08x\n", hres);
            uri = NULL;
        }
    }

    if(!uri) {
        WCHAR *url;

        hres = IMoniker_GetDisplayName(mon, NULL, NULL, &url);
        if(SUCCEEDED(hres)) {
            hres = create_uri(url, 0, &uri);
            if(FAILED(hres)) {
                WARN("CrateUri failed: %08x\n", hres);
                set_current_uri(This, NULL);
                This->url = SysAllocString(url);
                CoTaskMemFree(url);
                return;
            }
            CoTaskMemFree(url);
        }else {
            WARN("GetDisplayName failed: %08x\n", hres);
        }
    }

    set_current_uri(This, uri);
    if(uri)
        IUri_Release(uri);
    set_script_mode(This, use_gecko_script(This) ? SCRIPTMODE_GECKO : SCRIPTMODE_ACTIVESCRIPT);
}