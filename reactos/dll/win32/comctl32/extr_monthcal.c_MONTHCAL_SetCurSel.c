#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WORD ;
struct TYPE_18__ {int /*<<< orphan*/  wDay; scalar_t__ wMilliseconds; scalar_t__ wSecond; scalar_t__ wMinute; scalar_t__ wHour; } ;
struct TYPE_19__ {int dwStyle; int /*<<< orphan*/  hwndSelf; TYPE_2__ maxSel; TYPE_2__ minSel; TYPE_1__* calendars; } ;
struct TYPE_17__ {int /*<<< orphan*/  month; } ;
typedef  TYPE_2__ SYSTEMTIME ;
typedef  int /*<<< orphan*/  RECT ;
typedef  TYPE_3__ MONTHCAL_INFO ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  scalar_t__ INT ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MCS_MULTISELECT ; 
 int /*<<< orphan*/  MONTHCAL_CalculateDayOfWeek (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ MONTHCAL_GetCalCount (TYPE_3__*) ; 
 int /*<<< orphan*/  MONTHCAL_GetDayRect (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  MONTHCAL_GetMonth (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ MONTHCAL_IsDateEqual (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  MONTHCAL_IsDateInValidRange (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ MONTHCAL_MonthDiff (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  MONTHCAL_ValidateDate (TYPE_2__*) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static LRESULT
MONTHCAL_SetCurSel(MONTHCAL_INFO *infoPtr, SYSTEMTIME *curSel)
{
  SYSTEMTIME prev = infoPtr->minSel, selection;
  INT diff;
  WORD day;

  TRACE("%p\n", curSel);
  if(!curSel) return FALSE;
  if(infoPtr->dwStyle & MCS_MULTISELECT) return FALSE;

  if(!MONTHCAL_ValidateDate(curSel)) return FALSE;
  /* exit earlier if selection equals current */
  if (MONTHCAL_IsDateEqual(&infoPtr->minSel, curSel)) return TRUE;

  selection = *curSel;
  selection.wHour = selection.wMinute = selection.wSecond = selection.wMilliseconds = 0;
  MONTHCAL_CalculateDayOfWeek(&selection, TRUE);

  if(!MONTHCAL_IsDateInValidRange(infoPtr, &selection, FALSE)) return FALSE;

  /* scroll calendars only if we have to */
  diff = MONTHCAL_MonthDiff(&infoPtr->calendars[MONTHCAL_GetCalCount(infoPtr)-1].month, curSel);
  if (diff <= 0)
  {
    diff = MONTHCAL_MonthDiff(&infoPtr->calendars[0].month, curSel);
    if (diff > 0) diff = 0;
  }

  if (diff != 0)
  {
    INT i;

    for (i = 0; i < MONTHCAL_GetCalCount(infoPtr); i++)
      MONTHCAL_GetMonth(&infoPtr->calendars[i].month, diff);
  }

  /* we need to store time part as it is */
  selection = *curSel;
  MONTHCAL_CalculateDayOfWeek(&selection, TRUE);
  infoPtr->minSel = infoPtr->maxSel = selection;

  /* if selection is still in current month, reduce rectangle */
  day = prev.wDay;
  prev.wDay = curSel->wDay;
  if (MONTHCAL_IsDateEqual(&prev, curSel))
  {
    RECT r_prev, r_new;

    prev.wDay = day;
    MONTHCAL_GetDayRect(infoPtr, &prev, &r_prev, -1);
    MONTHCAL_GetDayRect(infoPtr, curSel, &r_new, -1);

    InvalidateRect(infoPtr->hwndSelf, &r_prev, FALSE);
    InvalidateRect(infoPtr->hwndSelf, &r_new,  FALSE);
  }
  else
    InvalidateRect(infoPtr->hwndSelf, NULL, FALSE);

  return TRUE;
}