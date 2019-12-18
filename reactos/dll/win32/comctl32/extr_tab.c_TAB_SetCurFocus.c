#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int uFocus; int iSelected; int uNumItem; int dwStyle; int /*<<< orphan*/  hwnd; } ;
typedef  TYPE_1__ TAB_INFO ;
typedef  int /*<<< orphan*/  RECT ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int INT ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAB_EnsureSelectionVisible (TYPE_1__*) ; 
 scalar_t__ TAB_InternalGetItemRect (TYPE_1__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAB_InvalidateTabArea (TYPE_1__*) ; 
 int /*<<< orphan*/  TAB_SendSimpleNotify (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCN_FOCUSCHANGE ; 
 int /*<<< orphan*/  TCN_SELCHANGE ; 
 int /*<<< orphan*/  TCN_SELCHANGING ; 
 int TCS_BUTTONS ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*,int) ; 

__attribute__((used)) static LRESULT TAB_SetCurFocus (TAB_INFO *infoPtr, INT iItem)
{
  TRACE("(%p %d)\n", infoPtr, iItem);

  if (iItem < 0) {
      infoPtr->uFocus = -1;
      if (infoPtr->iSelected != -1) {
          infoPtr->iSelected = -1;
          TAB_SendSimpleNotify(infoPtr, TCN_SELCHANGE);
          TAB_InvalidateTabArea(infoPtr);
      }
  }
  else if (iItem < infoPtr->uNumItem) {
    if (infoPtr->dwStyle & TCS_BUTTONS) {
      /* set focus to new item, leave selection as is */
      if (infoPtr->uFocus != iItem) {
        INT prev_focus = infoPtr->uFocus;
        RECT r;

        infoPtr->uFocus = iItem;

        if (prev_focus != infoPtr->iSelected) {
          if (TAB_InternalGetItemRect(infoPtr, prev_focus, &r, NULL))
            InvalidateRect(infoPtr->hwnd, &r, FALSE);
        }

        if (TAB_InternalGetItemRect(infoPtr, iItem, &r, NULL))
            InvalidateRect(infoPtr->hwnd, &r, FALSE);

        TAB_SendSimpleNotify(infoPtr, TCN_FOCUSCHANGE);
      }
    } else {
      INT oldFocus = infoPtr->uFocus;
      if (infoPtr->iSelected != iItem || oldFocus == -1 ) {
        infoPtr->uFocus = iItem;
        if (oldFocus != -1) {
          if (!TAB_SendSimpleNotify(infoPtr, TCN_SELCHANGING))  {
            infoPtr->iSelected = iItem;
            TAB_SendSimpleNotify(infoPtr, TCN_SELCHANGE);
          }
          else
            infoPtr->iSelected = iItem;
          TAB_EnsureSelectionVisible(infoPtr);
          TAB_InvalidateTabArea(infoPtr);
        }
      }
    }
  }
  return 0;
}