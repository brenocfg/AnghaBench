#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_9__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int WPARAM ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_14__ {int dwState; } ;
struct TYPE_13__ {short x; short y; } ;
struct TYPE_12__ {int dwStyle; int iSelected; int uNumItem; int /*<<< orphan*/  hwnd; scalar_t__ hwndToolTip; } ;
typedef  TYPE_1__ TAB_INFO ;
typedef  int /*<<< orphan*/  RECT ;
typedef  TYPE_2__ POINT ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int INT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ HIWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LOWORD (int /*<<< orphan*/ ) ; 
 int MK_CONTROL ; 
 int /*<<< orphan*/  SetFocus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAB_DeselectAll (TYPE_1__*,scalar_t__) ; 
 TYPE_9__* TAB_GetItem (TYPE_1__*,int) ; 
 scalar_t__ TAB_InternalGetItemRect (TYPE_1__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int TAB_InternalHitTest (TYPE_1__*,TYPE_2__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAB_RelayEvent (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ TAB_SendSimpleNotify (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAB_SetCurSel (TYPE_1__*,int) ; 
 int TCIS_BUTTONPRESSED ; 
 int /*<<< orphan*/  TCN_SELCHANGE ; 
 int /*<<< orphan*/  TCN_SELCHANGING ; 
 int TCS_BUTTONS ; 
 int TCS_FOCUSNEVER ; 
 int TCS_MULTISELECT ; 
 int /*<<< orphan*/  TRACE (char*,int) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WM_LBUTTONDOWN ; 

__attribute__((used)) static LRESULT
TAB_LButtonDown (TAB_INFO *infoPtr, WPARAM wParam, LPARAM lParam)
{
  POINT pt;
  INT newItem;
  UINT dummy;

  if (infoPtr->hwndToolTip)
    TAB_RelayEvent (infoPtr->hwndToolTip, infoPtr->hwnd,
		    WM_LBUTTONDOWN, wParam, lParam);

  if (!(infoPtr->dwStyle & TCS_FOCUSNEVER)) {
    SetFocus (infoPtr->hwnd);
  }

  if (infoPtr->hwndToolTip)
    TAB_RelayEvent (infoPtr->hwndToolTip, infoPtr->hwnd,
		    WM_LBUTTONDOWN, wParam, lParam);

  pt.x = (short)LOWORD(lParam);
  pt.y = (short)HIWORD(lParam);

  newItem = TAB_InternalHitTest (infoPtr, pt, &dummy);

  TRACE("On Tab, item %d\n", newItem);

  if ((newItem != -1) && (infoPtr->iSelected != newItem))
  {
    if ((infoPtr->dwStyle & TCS_BUTTONS) && (infoPtr->dwStyle & TCS_MULTISELECT) &&
        (wParam & MK_CONTROL))
    {
      RECT r;

      /* toggle multiselection */
      TAB_GetItem(infoPtr, newItem)->dwState ^= TCIS_BUTTONPRESSED;
      if (TAB_InternalGetItemRect (infoPtr, newItem, &r, NULL))
        InvalidateRect (infoPtr->hwnd, &r, TRUE);
    }
    else
    {
      INT i;
      BOOL pressed = FALSE;

      /* any button pressed ? */
      for (i = 0; i < infoPtr->uNumItem; i++)
        if ((TAB_GetItem (infoPtr, i)->dwState & TCIS_BUTTONPRESSED) &&
            (infoPtr->iSelected != i))
        {
          pressed = TRUE;
          break;
        }

      if (TAB_SendSimpleNotify(infoPtr, TCN_SELCHANGING))
        return 0;

      if (pressed)
        TAB_DeselectAll (infoPtr, FALSE);
      else
        TAB_SetCurSel(infoPtr, newItem);

      TAB_SendSimpleNotify(infoPtr, TCN_SELCHANGE);
    }
  }

  return 0;
}