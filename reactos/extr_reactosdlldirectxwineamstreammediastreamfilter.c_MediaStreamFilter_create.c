#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  IBaseFilter_iface; } ;
struct TYPE_4__ {TYPE_3__ filter; } ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  TYPE_1__ IMediaStreamFilterImpl ;
typedef  int /*<<< orphan*/  IBaseFilterVtbl ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD_PTR ;

/* Variables and functions */
 int /*<<< orphan*/  BaseFilter_Init (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BaseFuncTable ; 
 int /*<<< orphan*/  CLASS_E_NOAGGREGATION ; 
 int /*<<< orphan*/  CLSID_MediaStreamFilter ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MediaStreamFilter_Vtbl ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,void**) ; 

HRESULT MediaStreamFilter_create(IUnknown *pUnkOuter, void **ppObj)
{
    IMediaStreamFilterImpl* object;

    TRACE("(%p,%p)\n", pUnkOuter, ppObj);

    if( pUnkOuter )
        return CLASS_E_NOAGGREGATION;

    object = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(IMediaStreamFilterImpl));
    if (!object)
        return E_OUTOFMEMORY;

    BaseFilter_Init(&object->filter, (IBaseFilterVtbl*)&MediaStreamFilter_Vtbl, &CLSID_MediaStreamFilter, (DWORD_PTR)(__FILE__ ": MediaStreamFilterImpl.csFilter"), &BaseFuncTable);

    *ppObj = &object->filter.IBaseFilter_iface;

    return S_OK;
}