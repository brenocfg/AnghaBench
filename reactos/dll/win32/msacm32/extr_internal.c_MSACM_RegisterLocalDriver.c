#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WINE_ACMLOCALDRIVER ;
struct TYPE_7__ {scalar_t__ pACMDriverID; int /*<<< orphan*/  dwType; } ;
struct TYPE_8__ {scalar_t__ hModule; scalar_t__ lpDrvProc; int ref; struct TYPE_8__* pNextACMLocalDrv; struct TYPE_8__* pPrevACMLocalDrv; int /*<<< orphan*/ * pACMInstList; TYPE_1__ obj; } ;
typedef  TYPE_2__* PWINE_ACMLOCALDRIVER ;
typedef  scalar_t__ HMODULE ;
typedef  scalar_t__ DRIVERPROC ;

/* Variables and functions */
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  InterlockedIncrement (int*) ; 
 int /*<<< orphan*/  MSACM_hHeap ; 
 TYPE_2__* MSACM_pFirstACMLocalDriver ; 
 TYPE_2__* MSACM_pLastACMLocalDriver ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  WINE_ACMOBJ_LOCALDRIVER ; 

PWINE_ACMLOCALDRIVER MSACM_RegisterLocalDriver(HMODULE hModule, DRIVERPROC lpDriverProc)
{
    PWINE_ACMLOCALDRIVER paldrv;

    TRACE("(%p, %p)\n", hModule, lpDriverProc);
    if (!hModule || !lpDriverProc) return NULL;
    
    /* look up previous instance of local driver module */
    for (paldrv = MSACM_pFirstACMLocalDriver; paldrv; paldrv = paldrv->pNextACMLocalDrv)
    {
        if (paldrv->hModule == hModule && paldrv->lpDrvProc == lpDriverProc)
        {
            InterlockedIncrement(&paldrv->ref);
            return paldrv;
        }
    }

    paldrv = HeapAlloc(MSACM_hHeap, 0, sizeof(WINE_ACMLOCALDRIVER));
    paldrv->obj.dwType = WINE_ACMOBJ_LOCALDRIVER;
    paldrv->obj.pACMDriverID = 0;
    paldrv->hModule = hModule;
    paldrv->lpDrvProc = lpDriverProc;
    paldrv->pACMInstList = NULL;
    paldrv->ref = 1;

    paldrv->pNextACMLocalDrv = NULL;
    paldrv->pPrevACMLocalDrv = MSACM_pLastACMLocalDriver;
    if (MSACM_pLastACMLocalDriver)
	MSACM_pLastACMLocalDriver->pNextACMLocalDrv = paldrv;
    MSACM_pLastACMLocalDriver = paldrv;
    if (!MSACM_pFirstACMLocalDriver)
	MSACM_pFirstACMLocalDriver = paldrv;

    return paldrv;
}