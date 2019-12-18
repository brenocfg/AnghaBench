#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_6__ {int dwSize; } ;
struct TYPE_7__ {int ref; TYPE_3__ IReferenceClock_iface; TYPE_1__ pClockInfo; scalar_t__ rtTime; } ;
typedef  int /*<<< orphan*/ * LPVOID ;
typedef  int /*<<< orphan*/  LPUNKNOWN ;
typedef  int /*<<< orphan*/  LPCGUID ;
typedef  TYPE_2__ IReferenceClockImpl ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DMUS_CLOCKINFO ;

/* Variables and functions */
 int /*<<< orphan*/  DMUSIC_LockModule () ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IReferenceClockImpl_QueryInterface (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IReferenceClock_Release (TYPE_3__*) ; 
 int /*<<< orphan*/  ReferenceClock_Vtbl ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_guid (int /*<<< orphan*/ ) ; 

HRESULT DMUSIC_CreateReferenceClockImpl(LPCGUID riid, LPVOID* ret_iface, LPUNKNOWN unkouter)
{
    IReferenceClockImpl* clock;
    HRESULT hr;

    TRACE("(%s, %p, %p)\n", debugstr_guid(riid), ret_iface, unkouter);

    clock = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(IReferenceClockImpl));
    if (!clock) {
        *ret_iface = NULL;
        return E_OUTOFMEMORY;
    }

    clock->IReferenceClock_iface.lpVtbl = &ReferenceClock_Vtbl;
    clock->ref = 1;
    clock->rtTime = 0;
    clock->pClockInfo.dwSize = sizeof (DMUS_CLOCKINFO);

    DMUSIC_LockModule();
    hr = IReferenceClockImpl_QueryInterface(&clock->IReferenceClock_iface, riid, ret_iface);
    IReferenceClock_Release(&clock->IReferenceClock_iface);

    return hr;
}