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
struct TYPE_7__ {scalar_t__ pLocalDriver; struct TYPE_7__* pNextACMDriverID; struct TYPE_7__* pPrevACMDriverID; struct TYPE_7__* aFormatTag; struct TYPE_7__* pszFileName; struct TYPE_7__* pszDriverAlias; scalar_t__ pACMDriverList; } ;
typedef  TYPE_1__* PWINE_ACMDRIVERID ;
typedef  int /*<<< orphan*/  HACMDRIVER ;

/* Variables and functions */
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  MSACM_UnregisterLocalDriver (scalar_t__) ; 
 int /*<<< orphan*/  MSACM_hHeap ; 
 TYPE_1__* MSACM_pFirstACMDriverID ; 
 TYPE_1__* MSACM_pLastACMDriverID ; 
 int /*<<< orphan*/  acmDriverClose (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

PWINE_ACMDRIVERID MSACM_UnregisterDriver(PWINE_ACMDRIVERID p)
{
    PWINE_ACMDRIVERID pNextACMDriverID;

    while (p->pACMDriverList)
	acmDriverClose((HACMDRIVER) p->pACMDriverList, 0);

    HeapFree(MSACM_hHeap, 0, p->pszDriverAlias);
    HeapFree(MSACM_hHeap, 0, p->pszFileName);
    HeapFree(MSACM_hHeap, 0, p->aFormatTag);

    if (p == MSACM_pFirstACMDriverID)
	MSACM_pFirstACMDriverID = p->pNextACMDriverID;
    if (p == MSACM_pLastACMDriverID)
	MSACM_pLastACMDriverID = p->pPrevACMDriverID;

    if (p->pPrevACMDriverID)
	p->pPrevACMDriverID->pNextACMDriverID = p->pNextACMDriverID;
    if (p->pNextACMDriverID)
	p->pNextACMDriverID->pPrevACMDriverID = p->pPrevACMDriverID;

    pNextACMDriverID = p->pNextACMDriverID;

    if (p->pLocalDriver) MSACM_UnregisterLocalDriver(p->pLocalDriver);
    HeapFree(MSACM_hHeap, 0, p);

    return pNextACMDriverID;
}