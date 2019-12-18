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
struct TYPE_6__ {int x; int y; } ;
struct TYPE_5__ {scalar_t__ dwValueLen; scalar_t__ lpValue; } ;
typedef  TYPE_1__* PTHEME_PROPERTY ;
typedef  TYPE_2__ POINT ;
typedef  scalar_t__ LPCWSTR ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_PROP_ID_UNSUPPORTED ; 
 int /*<<< orphan*/  MSSTYLES_GetNextInteger (scalar_t__,scalar_t__,scalar_t__*,int*) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 

HRESULT MSSTYLES_GetPropertyPosition(PTHEME_PROPERTY tp, POINT *pPoint)
{
    int x,y;
    LPCWSTR lpCur = tp->lpValue;
    LPCWSTR lpEnd = tp->lpValue + tp->dwValueLen;

    if(!MSSTYLES_GetNextInteger(lpCur, lpEnd, &lpCur, &x)) {
        TRACE("Could not parse position property\n");
        return E_PROP_ID_UNSUPPORTED;
    }
    if(!MSSTYLES_GetNextInteger(lpCur, lpEnd, &lpCur, &y)) {
        TRACE("Could not parse position property\n");
        return E_PROP_ID_UNSUPPORTED;
    }
    pPoint->x = x;
    pPoint->y = y;
    return S_OK;
}