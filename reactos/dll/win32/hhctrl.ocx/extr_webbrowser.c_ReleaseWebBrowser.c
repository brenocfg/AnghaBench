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
struct TYPE_4__ {int /*<<< orphan*/  IOleClientSite_iface; scalar_t__ ole_obj; } ;
typedef  TYPE_1__ WebBrowserContainer ;
struct TYPE_5__ {TYPE_1__* web_browser; } ;
typedef  int /*<<< orphan*/  IOleInPlaceSite ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_2__ HHInfo ;

/* Variables and functions */
 int /*<<< orphan*/  IID_IOleInPlaceSite ; 
 int /*<<< orphan*/  IOleClientSite_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IOleInPlaceSite_OnInPlaceDeactivate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IOleInPlaceSite_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IOleObject_QueryInterface (scalar_t__,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IOleObject_SetClientSite (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 

void ReleaseWebBrowser(HHInfo *info)
{
    WebBrowserContainer *container = info->web_browser;
    HRESULT hres;

    if(!container)
        return;

    if(container->ole_obj) {
        IOleInPlaceSite *inplace;

        hres = IOleObject_QueryInterface(container->ole_obj, &IID_IOleInPlaceSite, (void**)&inplace);
        if(SUCCEEDED(hres)) {
            IOleInPlaceSite_OnInPlaceDeactivate(inplace);
            IOleInPlaceSite_Release(inplace);
        }

        IOleObject_SetClientSite(container->ole_obj, NULL);
    }

    info->web_browser = NULL;
    IOleClientSite_Release(&container->IOleClientSite_iface);
}