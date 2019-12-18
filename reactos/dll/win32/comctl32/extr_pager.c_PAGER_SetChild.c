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
struct TYPE_4__ {int hwndChild; int nPos; int /*<<< orphan*/  hwndSelf; } ;
typedef  TYPE_1__ PAGER_INFO ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int HWND ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ IsWindow (int) ; 
 int /*<<< orphan*/  PAGER_SetPos (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SWP_FRAMECHANGED ; 
 int SWP_NOACTIVATE ; 
 int SWP_NOMOVE ; 
 int SWP_NOSIZE ; 
 int SWP_NOZORDER ; 
 int /*<<< orphan*/  SetWindowPos (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static LRESULT
PAGER_SetChild (PAGER_INFO* infoPtr, HWND hwndChild)
{
    infoPtr->hwndChild = IsWindow (hwndChild) ? hwndChild : 0;

    if (infoPtr->hwndChild)
    {
        TRACE("[%p] hwndChild=%p\n", infoPtr->hwndSelf, infoPtr->hwndChild);

        SetWindowPos(infoPtr->hwndSelf, 0, 0, 0, 0, 0,
                     SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE);

        infoPtr->nPos = -1;
        PAGER_SetPos(infoPtr, 0, FALSE, FALSE);
    }

    return 0;
}