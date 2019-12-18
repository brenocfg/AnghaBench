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
struct TYPE_6__ {scalar_t__ dwValueLen; scalar_t__ lpValue; } ;
struct TYPE_5__ {int /*<<< orphan*/  bottom; int /*<<< orphan*/  right; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
typedef  TYPE_1__ RECT ;
typedef  TYPE_2__* PTHEME_PROPERTY ;
typedef  scalar_t__ LPCWSTR ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_PROP_ID_UNSUPPORTED ; 
 int /*<<< orphan*/  MSSTYLES_GetNextInteger (scalar_t__,scalar_t__,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 

HRESULT MSSTYLES_GetPropertyRect(PTHEME_PROPERTY tp, RECT *pRect)
{
    LPCWSTR lpCur = tp->lpValue;
    LPCWSTR lpEnd = tp->lpValue + tp->dwValueLen;

    MSSTYLES_GetNextInteger(lpCur, lpEnd, &lpCur, &pRect->left);
    MSSTYLES_GetNextInteger(lpCur, lpEnd, &lpCur, &pRect->top);
    MSSTYLES_GetNextInteger(lpCur, lpEnd, &lpCur, &pRect->right);
    if(!MSSTYLES_GetNextInteger(lpCur, lpEnd, &lpCur, &pRect->bottom)) {
        TRACE("Could not parse rect property\n");
        return E_PROP_ID_UNSUPPORTED;
    }
    return S_OK;
}