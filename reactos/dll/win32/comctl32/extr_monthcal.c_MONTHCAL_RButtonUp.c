#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_10__ {int dwStyle; int /*<<< orphan*/  todaysDate; int /*<<< orphan*/  hwndSelf; } ;
struct TYPE_9__ {short x; short y; } ;
typedef  int /*<<< orphan*/  SYSTEMTIME ;
typedef  TYPE_1__ POINT ;
typedef  TYPE_2__ MONTHCAL_INFO ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HMENU ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AppendMenuW (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  COMCTL32_hModule ; 
 int /*<<< orphan*/  ClientToScreen (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  CreatePopupMenu () ; 
 scalar_t__ HIWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDM_GOTODAY ; 
 scalar_t__ LOWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MCS_MULTISELECT ; 
 int MF_ENABLED ; 
 int MF_STRING ; 
 int /*<<< orphan*/  MONTHCAL_NotifySelect (TYPE_2__*) ; 
 int /*<<< orphan*/  MONTHCAL_NotifySelectionChange (TYPE_2__*) ; 
 int /*<<< orphan*/  MONTHCAL_SetCurSel (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MONTHCAL_SetSelRange (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int TPM_NONOTIFY ; 
 int TPM_RETURNCMD ; 
 int TPM_RIGHTBUTTON ; 
 scalar_t__ TrackPopupMenu (int /*<<< orphan*/ ,int,short,short,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static LRESULT
MONTHCAL_RButtonUp(MONTHCAL_INFO *infoPtr, LPARAM lParam)
{
  HMENU hMenu;
  POINT menupoint;
  WCHAR buf[32];

  hMenu = CreatePopupMenu();
  LoadStringW(COMCTL32_hModule, IDM_GOTODAY, buf, ARRAY_SIZE(buf));
  AppendMenuW(hMenu, MF_STRING|MF_ENABLED, 1, buf);
  menupoint.x = (short)LOWORD(lParam);
  menupoint.y = (short)HIWORD(lParam);
  ClientToScreen(infoPtr->hwndSelf, &menupoint);
  if( TrackPopupMenu(hMenu, TPM_RIGHTBUTTON | TPM_NONOTIFY | TPM_RETURNCMD,
		     menupoint.x, menupoint.y, 0, infoPtr->hwndSelf, NULL))
  {
      if (infoPtr->dwStyle & MCS_MULTISELECT)
      {
          SYSTEMTIME range[2];

          range[0] = range[1] = infoPtr->todaysDate;
          MONTHCAL_SetSelRange(infoPtr, range);
      }
      else
          MONTHCAL_SetCurSel(infoPtr, &infoPtr->todaysDate);

      MONTHCAL_NotifySelectionChange(infoPtr);
      MONTHCAL_NotifySelect(infoPtr);
  }

  return 0;
}