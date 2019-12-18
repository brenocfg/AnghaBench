#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  hwnd; int /*<<< orphan*/  IOleClientSite_iface; int /*<<< orphan*/  document; } ;
typedef  int /*<<< orphan*/  RECT ;
typedef  int /*<<< orphan*/  IOleObject ;
typedef  int /*<<< orphan*/  IHlinkTarget ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_1__ DocHost ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*,...) ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IHlinkTarget_Navigate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IHlinkTarget_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IHlinkTarget ; 
 int /*<<< orphan*/  IID_IOleObject ; 
 int /*<<< orphan*/  IOleObject_DoVerb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IOleObject_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IUnknown_QueryInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  OLEIVERB_SHOW ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  WARN (char*) ; 

__attribute__((used)) static void object_available(DocHost *This)
{
    IHlinkTarget *hlink;
    HRESULT hres;

    TRACE("(%p)\n", This);

    if(!This->document) {
        WARN("document == NULL\n");
        return;
    }

    hres = IUnknown_QueryInterface(This->document, &IID_IHlinkTarget, (void**)&hlink);
    if(SUCCEEDED(hres)) {
        hres = IHlinkTarget_Navigate(hlink, 0, NULL);
        IHlinkTarget_Release(hlink);
        if(FAILED(hres))
            FIXME("Navigate failed\n");
    }else {
        IOleObject *ole_object;
        RECT rect;

        TRACE("No IHlink iface\n");

        hres = IUnknown_QueryInterface(This->document, &IID_IOleObject, (void**)&ole_object);
        if(FAILED(hres)) {
            FIXME("Could not get IOleObject iface: %08x\n", hres);
            return;
        }

        GetClientRect(This->hwnd, &rect);
        hres = IOleObject_DoVerb(ole_object, OLEIVERB_SHOW, NULL, &This->IOleClientSite_iface, -1, This->hwnd, &rect);
        IOleObject_Release(ole_object);
        if(FAILED(hres))
            FIXME("DoVerb failed: %08x\n", hres);
    }
}