#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_7__ {int ref; TYPE_1__ IAMMultiMediaStream_iface; } ;
typedef  TYPE_1__* LPVOID ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  TYPE_2__ IAMMultiMediaStreamImpl ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  AM_Vtbl ; 
 int /*<<< orphan*/  CLASS_E_NOAGGREGATION ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,TYPE_1__**) ; 

HRESULT AM_create(IUnknown *pUnkOuter, LPVOID *ppObj)
{
    IAMMultiMediaStreamImpl* object; 

    TRACE("(%p,%p)\n", pUnkOuter, ppObj);

    if( pUnkOuter )
        return CLASS_E_NOAGGREGATION;

    object = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(IAMMultiMediaStreamImpl));
    if (!object)
        return E_OUTOFMEMORY;

    object->IAMMultiMediaStream_iface.lpVtbl = &AM_Vtbl;
    object->ref = 1;

    *ppObj = &object->IAMMultiMediaStream_iface;

    return S_OK;
}