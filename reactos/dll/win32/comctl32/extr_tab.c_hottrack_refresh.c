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
struct TYPE_5__ {int /*<<< orphan*/  hwnd; } ;
typedef  TYPE_1__ TAB_INFO ;
typedef  int /*<<< orphan*/  RECT ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetWindowTheme (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAB_DrawLoneItemInterior (TYPE_1__ const*,int) ; 
 int /*<<< orphan*/  TAB_InternalGetItemRect (TYPE_1__ const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void hottrack_refresh(const TAB_INFO *infoPtr, int tabIndex)
{
    if (tabIndex == -1) return;

    if (GetWindowTheme (infoPtr->hwnd))
    {
        RECT rect;
        TAB_InternalGetItemRect(infoPtr, tabIndex, &rect, NULL);
        InvalidateRect (infoPtr->hwnd, &rect, FALSE);
    }
    else
        TAB_DrawLoneItemInterior(infoPtr, tabIndex);
}