#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_11__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_12__ {int ref; int version; TYPE_8__ IWebBrowser2_iface; int /*<<< orphan*/  doc_host; int /*<<< orphan*/  hlink_frame; void* tool_bar; void* status_bar; void* address_bar; void* menu_bar; void* visible; TYPE_1__ IServiceProvider_iface; } ;
typedef  TYPE_2__ WebBrowser ;
typedef  int /*<<< orphan*/  REFIID ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  DocHostContainerVtbl ; 
 int /*<<< orphan*/  DocHost_Init (int /*<<< orphan*/ *,TYPE_8__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HlinkFrame_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWebBrowser2_QueryInterface (TYPE_8__*,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  IWebBrowser2_Release (TYPE_8__*) ; 
 int /*<<< orphan*/  ServiceProviderVtbl ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void**,int) ; 
 void* VARIANT_TRUE ; 
 int /*<<< orphan*/  WebBrowser2Vtbl ; 
 int /*<<< orphan*/  WebBrowser_ClassInfo_Init (TYPE_2__*) ; 
 int /*<<< orphan*/  WebBrowser_OleObject_Init (TYPE_2__*) ; 
 int /*<<< orphan*/  WebBrowser_Persist_Init (TYPE_2__*) ; 
 int /*<<< orphan*/  WebBrowser_ViewObject_Init (TYPE_2__*) ; 
 int /*<<< orphan*/  debugstr_guid (int /*<<< orphan*/ ) ; 
 TYPE_2__* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  lock_module () ; 

__attribute__((used)) static HRESULT create_webbrowser(int version, IUnknown *outer, REFIID riid, void **ppv)
{
    WebBrowser *ret;
    HRESULT hres;

    TRACE("(%p %s %p) version=%d\n", outer, debugstr_guid(riid), ppv, version);

    ret = heap_alloc_zero(sizeof(WebBrowser));

    ret->IWebBrowser2_iface.lpVtbl = &WebBrowser2Vtbl;
    ret->IServiceProvider_iface.lpVtbl = &ServiceProviderVtbl;
    ret->ref = 1;
    ret->version = version;

    DocHost_Init(&ret->doc_host, &ret->IWebBrowser2_iface, &DocHostContainerVtbl);

    ret->visible = VARIANT_TRUE;
    ret->menu_bar = VARIANT_TRUE;
    ret->address_bar = VARIANT_TRUE;
    ret->status_bar = VARIANT_TRUE;
    ret->tool_bar = VARIANT_TRUE;

    WebBrowser_OleObject_Init(ret);
    WebBrowser_ViewObject_Init(ret);
    WebBrowser_Persist_Init(ret);
    WebBrowser_ClassInfo_Init(ret);

    HlinkFrame_Init(&ret->hlink_frame, (IUnknown*)&ret->IWebBrowser2_iface, &ret->doc_host);

    lock_module();

    hres = IWebBrowser2_QueryInterface(&ret->IWebBrowser2_iface, riid, ppv);

    IWebBrowser2_Release(&ret->IWebBrowser2_iface);
    return hres;
}