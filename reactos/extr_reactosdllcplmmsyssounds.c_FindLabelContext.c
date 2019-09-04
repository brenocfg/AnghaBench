#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  szName; } ;
struct TYPE_11__ {struct TYPE_11__* Next; int /*<<< orphan*/ * szValue; TYPE_6__* LabelMap; TYPE_6__* AppMap; } ;
struct TYPE_10__ {TYPE_2__* LabelContext; } ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  TYPE_1__* PSOUND_SCHEME_CONTEXT ;
typedef  TYPE_2__* PLABEL_CONTEXT ;
typedef  int /*<<< orphan*/  PGLOBAL_DATA ;
typedef  int /*<<< orphan*/  LABEL_CONTEXT ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (TYPE_6__*) ; 
 TYPE_6__* FindApp (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_6__* FindLabel (int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _T (char) ; 
 int /*<<< orphan*/  _tcsicmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

PLABEL_CONTEXT FindLabelContext(PGLOBAL_DATA pGlobalData, PSOUND_SCHEME_CONTEXT pSoundScheme, TCHAR * AppName, TCHAR * LabelName)
{
    PLABEL_CONTEXT pLabelContext;

    pLabelContext = pSoundScheme->LabelContext;

    while (pLabelContext)
    {
        ASSERT(pLabelContext->AppMap);
        ASSERT(pLabelContext->LabelMap);

        if (!_tcsicmp(pLabelContext->AppMap->szName, AppName) && !_tcsicmp(pLabelContext->LabelMap->szName, LabelName))
        {
            return pLabelContext;
        }
        pLabelContext = pLabelContext->Next;
    }

    pLabelContext = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(LABEL_CONTEXT));
    if (!pLabelContext)
        return NULL;

    pLabelContext->AppMap = FindApp(pGlobalData, AppName);
    pLabelContext->LabelMap = FindLabel(pGlobalData, pLabelContext->AppMap, LabelName);
    ASSERT(pLabelContext->AppMap);
    ASSERT(pLabelContext->LabelMap);
    pLabelContext->szValue[0] = _T('\0');
    pLabelContext->Next = pSoundScheme->LabelContext;
    pSoundScheme->LabelContext = pLabelContext;

    return pLabelContext;
}