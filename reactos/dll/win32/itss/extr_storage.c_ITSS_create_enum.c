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
struct TYPE_7__ {int ref; int /*<<< orphan*/ * current; int /*<<< orphan*/ * last; int /*<<< orphan*/ * first; TYPE_1__ IEnumSTATSTG_iface; } ;
typedef  TYPE_2__ IEnumSTATSTG_Impl ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IEnumSTATSTG_vtbl ; 
 int /*<<< orphan*/  ITSS_LockModule () ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*) ; 

__attribute__((used)) static IEnumSTATSTG_Impl *ITSS_create_enum( void )
{
    IEnumSTATSTG_Impl *stgenum;

    stgenum = HeapAlloc( GetProcessHeap(), 0, sizeof (IEnumSTATSTG_Impl) );
    stgenum->IEnumSTATSTG_iface.lpVtbl = &IEnumSTATSTG_vtbl;
    stgenum->ref = 1;
    stgenum->first = NULL;
    stgenum->last = NULL;
    stgenum->current = NULL;

    ITSS_LockModule();
    TRACE(" -> %p\n", stgenum );

    return stgenum;
}