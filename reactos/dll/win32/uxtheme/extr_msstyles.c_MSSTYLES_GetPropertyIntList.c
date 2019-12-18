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
struct TYPE_6__ {int iValueCount; int /*<<< orphan*/ * iValues; } ;
struct TYPE_5__ {scalar_t__ dwValueLen; scalar_t__ lpValue; } ;
typedef  TYPE_1__* PTHEME_PROPERTY ;
typedef  scalar_t__ LPCWSTR ;
typedef  TYPE_2__ INTLIST ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int MAX_INTLIST_COUNT ; 
 int /*<<< orphan*/  MSSTYLES_GetNextInteger (scalar_t__,scalar_t__,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 

HRESULT MSSTYLES_GetPropertyIntList(PTHEME_PROPERTY tp, INTLIST *pIntList)
{
    int i;
    LPCWSTR lpCur = tp->lpValue;
    LPCWSTR lpEnd = tp->lpValue + tp->dwValueLen;

    for(i=0; i < MAX_INTLIST_COUNT; i++) {
        if(!MSSTYLES_GetNextInteger(lpCur, lpEnd, &lpCur, &pIntList->iValues[i]))
            break;
    }
    pIntList->iValueCount = i;
    return S_OK;
}