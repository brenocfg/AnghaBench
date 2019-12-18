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
struct TYPE_4__ {int dwStyle; scalar_t__ uFocus; scalar_t__ iSelected; int /*<<< orphan*/  hwnd; } ;
typedef  TYPE_1__ TAB_INFO ;
typedef  int /*<<< orphan*/  RECT ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ TAB_InternalGetItemRect (TYPE_1__*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int TCS_BUTTONS ; 

__attribute__((used)) static void TAB_KillFocus(TAB_INFO *infoPtr)
{
  /* clear current focused item back to selected for TCS_BUTTONS */
  if ((infoPtr->dwStyle & TCS_BUTTONS) && (infoPtr->uFocus != infoPtr->iSelected))
  {
    RECT r;

    if (TAB_InternalGetItemRect(infoPtr, infoPtr->uFocus, &r, NULL))
      InvalidateRect(infoPtr->hwnd, &r, FALSE);

    infoPtr->uFocus = infoPtr->iSelected;
  }
}