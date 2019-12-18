#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_5__ {TYPE_2__ ITfCompartmentMgr_iface; int /*<<< orphan*/  values; int /*<<< orphan*/ * pUnkOuter; } ;
typedef  int /*<<< orphan*/  REFIID ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_1__ CompartmentMgr ;

/* Variables and functions */
 int /*<<< orphan*/  CLASS_E_NOAGGREGATION ; 
 int /*<<< orphan*/  CompartmentMgrVtbl ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  E_POINTER ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 int /*<<< orphan*/  ITfCompartmentMgr_QueryInterface (TYPE_2__*,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  IsEqualIID (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 

HRESULT CompartmentMgr_Constructor(IUnknown *pUnkOuter, REFIID riid, IUnknown **ppOut)
{
    CompartmentMgr *This;

    if (!ppOut)
        return E_POINTER;

    if (pUnkOuter && !IsEqualIID (riid, &IID_IUnknown))
        return CLASS_E_NOAGGREGATION;

    This = HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,sizeof(CompartmentMgr));
    if (This == NULL)
        return E_OUTOFMEMORY;

    This->ITfCompartmentMgr_iface.lpVtbl = &CompartmentMgrVtbl;
    This->pUnkOuter = pUnkOuter;
    list_init(&This->values);

    if (pUnkOuter)
    {
        *ppOut = (IUnknown*)&This->ITfCompartmentMgr_iface;
        TRACE("returning %p\n", *ppOut);
        return S_OK;
    }
    else
    {
        HRESULT hr;
        hr = ITfCompartmentMgr_QueryInterface(&This->ITfCompartmentMgr_iface, riid, (void**)ppOut);
        if (FAILED(hr))
            HeapFree(GetProcessHeap(),0,This);
        return hr;
    }
}