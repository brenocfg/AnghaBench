#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int ref; int /*<<< orphan*/  entry; int /*<<< orphan*/  doc_host; int /*<<< orphan*/  IWebBrowser2_iface; int /*<<< orphan*/  hlink_frame; } ;
typedef  TYPE_1__ InternetExplorer ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  DocHostContainerVtbl ; 
 int /*<<< orphan*/  DocHost_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  HlinkFrame_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InterlockedIncrement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InternetExplorer_WebBrowser_Init (TYPE_1__*) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  create_frame_hwnd (TYPE_1__*) ; 
 TYPE_1__* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  ie_list ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obj_cnt ; 

__attribute__((used)) static HRESULT create_ie(InternetExplorer **ret_obj)
{
    InternetExplorer *ret;

    ret = heap_alloc_zero(sizeof(InternetExplorer));
    if(!ret)
        return E_OUTOFMEMORY;

    ret->ref = 1;

    DocHost_Init(&ret->doc_host, &ret->IWebBrowser2_iface, &DocHostContainerVtbl);

    InternetExplorer_WebBrowser_Init(ret);

    HlinkFrame_Init(&ret->hlink_frame, (IUnknown*)&ret->IWebBrowser2_iface, &ret->doc_host);

    create_frame_hwnd(ret);

    InterlockedIncrement(&obj_cnt);
    list_add_tail(&ie_list, &ret->entry);
    *ret_obj = ret;
    return S_OK;
}