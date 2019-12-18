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
struct TYPE_7__ {int /*<<< orphan*/ * lpVtbl; } ;
struct master_clock {int ref; double freq; TYPE_2__ IReferenceClock_iface; } ;
struct TYPE_6__ {double QuadPart; } ;
typedef  TYPE_1__ LARGE_INTEGER ;
typedef  TYPE_2__ IReferenceClock ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  QueryPerformanceFrequency (TYPE_1__*) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__**) ; 
 struct master_clock* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  master_clock_vtbl ; 

__attribute__((used)) static HRESULT master_clock_create(IReferenceClock **clock)
{
    struct master_clock *obj;
    LARGE_INTEGER freq;

    TRACE("(%p)\n", clock);

    if (!(obj = heap_alloc_zero(sizeof(*obj))))
        return E_OUTOFMEMORY;

    obj->IReferenceClock_iface.lpVtbl = &master_clock_vtbl;
    obj->ref = 1;
    QueryPerformanceFrequency(&freq);
    obj->freq = 10000000.0 / freq.QuadPart;

    *clock = &obj->IReferenceClock_iface;

    return S_OK;
}