#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ dwSpecialId; int /*<<< orphan*/  dwId; struct TYPE_4__* pNext; } ;
typedef  TYPE_1__ LAYOUT_LIST_NODE ;
typedef  int /*<<< orphan*/  HKL ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int HIWORD (int /*<<< orphan*/ ) ; 
 int LOWORD (int /*<<< orphan*/ ) ; 
 TYPE_1__* _LayoutList ; 

LAYOUT_LIST_NODE*
LayoutList_GetByHkl(HKL hkl)
{
    LAYOUT_LIST_NODE *pCurrent;

    if ((HIWORD(hkl) & 0xF000) == 0xF000)
    {
        DWORD dwSpecialId = (HIWORD(hkl) & 0x0FFF);

        for (pCurrent = _LayoutList; pCurrent != NULL; pCurrent = pCurrent->pNext)
        {
            if (dwSpecialId == pCurrent->dwSpecialId)
            {
                return pCurrent;
            }
        }
    }
    else
    {
        for (pCurrent = _LayoutList; pCurrent != NULL; pCurrent = pCurrent->pNext)
        {
            if (HIWORD(hkl) == LOWORD(pCurrent->dwId))
            {
                return pCurrent;
            }
        }
    }

    return NULL;
}