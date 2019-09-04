#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_1__* LabelMap; } ;
struct TYPE_13__ {TYPE_1__* pLabelMap; } ;
struct TYPE_12__ {struct TYPE_12__* Next; TYPE_3__* AppMap; struct TYPE_12__* szName; struct TYPE_12__* szDesc; } ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  TYPE_1__* PLABEL_MAP ;
typedef  TYPE_2__* PGLOBAL_DATA ;
typedef  TYPE_3__* PAPP_MAP ;
typedef  int /*<<< orphan*/  LABEL_MAP ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (TYPE_1__*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  _tcscmp (TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* _tcsdup (int /*<<< orphan*/ *) ; 

PLABEL_MAP FindLabel(PGLOBAL_DATA pGlobalData, PAPP_MAP pAppMap, TCHAR * szName)
{
    PLABEL_MAP pMap = pGlobalData->pLabelMap;

    while (pMap)
    {
        ASSERT(pMap);
        ASSERT(pMap->szName);
        if (!_tcscmp(pMap->szName, szName))
            return pMap;

        pMap = pMap->Next;
    }

    pMap = pAppMap->LabelMap;

    while (pMap)
    {
        ASSERT(pMap);
        ASSERT(pMap->szName);
        if (!_tcscmp(pMap->szName, szName))
            return pMap;

        pMap = pMap->Next;
    }

    pMap = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(LABEL_MAP));
    if (!pMap)
        return NULL;

    pMap->szName = pMap->szDesc = _tcsdup(szName);
    if (!pMap->szName)
    {
        HeapFree(GetProcessHeap(), 0, pMap);
        return NULL;
    }

    pMap->AppMap = pAppMap;
    pMap->Next = pGlobalData->pLabelMap;
    pGlobalData->pLabelMap = pMap;

    return pMap;
}