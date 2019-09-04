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
struct TYPE_4__ {int /*<<< orphan*/  dwId; struct TYPE_4__* pNext; } ;
typedef  TYPE_1__ LOCALE_LIST_NODE ;
typedef  int /*<<< orphan*/  HKL ;

/* Variables and functions */
 scalar_t__ LOWORD (int /*<<< orphan*/ ) ; 
 TYPE_1__* _LocaleList ; 

LOCALE_LIST_NODE*
LocaleList_GetByHkl(HKL hkl)
{
    LOCALE_LIST_NODE *pCurrent;

    for (pCurrent = _LocaleList; pCurrent != NULL; pCurrent = pCurrent->pNext)
    {
        if (LOWORD(pCurrent->dwId) == LOWORD(hkl))
        {
            return pCurrent;
        }
    }

    return NULL;
}