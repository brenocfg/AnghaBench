#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__* pNextACMLocalDrv; struct TYPE_7__* pPrevACMLocalDrv; int /*<<< orphan*/  ref; scalar_t__ pACMInstList; } ;
typedef  TYPE_1__* PWINE_ACMLOCALDRIVER ;
typedef  scalar_t__ LONG ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ InterlockedDecrement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MSACM_hHeap ; 
 TYPE_1__* MSACM_pFirstACMLocalDriver ; 
 TYPE_1__* MSACM_pLastACMLocalDriver ; 

__attribute__((used)) static PWINE_ACMLOCALDRIVER MSACM_UnregisterLocalDriver(PWINE_ACMLOCALDRIVER paldrv)
{
    PWINE_ACMLOCALDRIVER pNextACMLocalDriver;
    LONG ref;

    if (paldrv->pACMInstList) {
        ERR("local driver instances still present after closing all drivers - memory leak\n");
        return NULL;
    }

    ref = InterlockedDecrement(&paldrv->ref);
    if (ref)
        return paldrv;

    if (paldrv == MSACM_pFirstACMLocalDriver)
        MSACM_pFirstACMLocalDriver = paldrv->pNextACMLocalDrv;
    if (paldrv == MSACM_pLastACMLocalDriver)
        MSACM_pLastACMLocalDriver = paldrv->pPrevACMLocalDrv;

    if (paldrv->pPrevACMLocalDrv)
        paldrv->pPrevACMLocalDrv->pNextACMLocalDrv = paldrv->pNextACMLocalDrv;
    if (paldrv->pNextACMLocalDrv)
        paldrv->pNextACMLocalDrv->pPrevACMLocalDrv = paldrv->pPrevACMLocalDrv;

    pNextACMLocalDriver = paldrv->pNextACMLocalDrv;

    HeapFree(MSACM_hHeap, 0, paldrv);

    return pNextACMLocalDriver;
}