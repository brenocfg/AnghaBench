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
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_6__ {TYPE_1__* pLabelMap; } ;
struct TYPE_5__ {struct TYPE_5__* Next; } ;
typedef  TYPE_1__* PLABEL_MAP ;
typedef  TYPE_2__* PGLOBAL_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static
VOID
FreeLabelMap(PGLOBAL_DATA pGlobalData)
{
    PLABEL_MAP pCurMap;

    while (pGlobalData->pLabelMap)
    {
        pCurMap = pGlobalData->pLabelMap->Next;
        HeapFree(GetProcessHeap(), 0, pGlobalData->pLabelMap);
        pGlobalData->pLabelMap = pCurMap;
    }
}