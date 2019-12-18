#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* pNextACMInst; } ;
typedef  TYPE_1__ WINE_ACMLOCALDRIVERINST ;
struct TYPE_7__ {scalar_t__ hModule; scalar_t__ lpDrvProc; TYPE_1__* pACMInstList; struct TYPE_7__* pNextACMLocalDrv; } ;
typedef  TYPE_1__* PWINE_ACMLOCALDRIVERINST ;
typedef  TYPE_3__* PWINE_ACMLOCALDRIVER ;
typedef  scalar_t__ HMODULE ;
typedef  scalar_t__ DRIVERPROC ;

/* Variables and functions */
 TYPE_3__* MSACM_pFirstACMLocalDriver ; 

__attribute__((used)) static unsigned MSACM_GetNumberOfModuleRefs(HMODULE hModule, DRIVERPROC lpDrvProc, WINE_ACMLOCALDRIVERINST ** found)
{
    PWINE_ACMLOCALDRIVER lpDrv;
    unsigned		count = 0;

    if (found) *found = NULL;
    for (lpDrv = MSACM_pFirstACMLocalDriver; lpDrv; lpDrv = lpDrv->pNextACMLocalDrv)
    {
	if (lpDrv->hModule == hModule && lpDrv->lpDrvProc == lpDrvProc)
        {
            PWINE_ACMLOCALDRIVERINST pInst = lpDrv->pACMInstList;
        
	    while (pInst) {
                if (found && !*found) *found = pInst;
	        count++;
	        pInst = pInst->pNextACMInst;
	    }
	}
    }
    return count;
}