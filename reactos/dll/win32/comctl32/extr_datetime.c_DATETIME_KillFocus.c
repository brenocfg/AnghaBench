#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  hwndSelf; scalar_t__ haveFocus; } ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  TYPE_1__ DATETIME_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  DATETIME_SendSimpleNotify (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DATETIME_SetSelectedField (TYPE_1__*,int) ; 
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NM_KILLFOCUS ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static LRESULT
DATETIME_KillFocus (DATETIME_INFO *infoPtr, HWND lostFocus)
{
    TRACE("lost focus to %p\n", lostFocus);

    if (infoPtr->haveFocus) {
	DATETIME_SendSimpleNotify (infoPtr, NM_KILLFOCUS);
	infoPtr->haveFocus = 0;
        DATETIME_SetSelectedField (infoPtr, -1);
    }

    InvalidateRect (infoPtr->hwndSelf, NULL, TRUE);

    return 0;
}