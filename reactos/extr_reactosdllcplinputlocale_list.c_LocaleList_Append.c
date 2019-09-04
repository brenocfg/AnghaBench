#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_6__ {struct TYPE_6__* pNext; struct TYPE_6__* pPrev; int /*<<< orphan*/  dwId; int /*<<< orphan*/ * pszName; } ;
typedef  TYPE_1__ LOCALE_LIST_NODE ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ZeroMemory (TYPE_1__*,int) ; 
 TYPE_1__* _LocaleList ; 
 int /*<<< orphan*/ * _wcsdup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ malloc (int) ; 

__attribute__((used)) static LOCALE_LIST_NODE*
LocaleList_Append(DWORD dwId, const WCHAR *pszName)
{
    LOCALE_LIST_NODE *pCurrent;
    LOCALE_LIST_NODE *pNew;

    if (pszName == NULL)
        return NULL;

    pCurrent = _LocaleList;

    pNew = (LOCALE_LIST_NODE*)malloc(sizeof(LOCALE_LIST_NODE));
    if (pNew == NULL)
        return NULL;

    ZeroMemory(pNew, sizeof(LOCALE_LIST_NODE));

    pNew->pszName = _wcsdup(pszName);
    if (pNew->pszName == NULL)
    {
        free(pNew);
        return NULL;
    }

    pNew->dwId = dwId;

    if (pCurrent == NULL)
    {
        _LocaleList = pNew;
    }
    else
    {
        while (pCurrent->pNext != NULL)
        {
            pCurrent = pCurrent->pNext;
        }

        pNew->pPrev = pCurrent;
        pCurrent->pNext = pNew;
    }

    return pNew;
}