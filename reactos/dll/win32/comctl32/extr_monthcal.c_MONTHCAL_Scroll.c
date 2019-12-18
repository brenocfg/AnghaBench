#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int dwStyle; int /*<<< orphan*/  minSel; TYPE_1__* calendars; } ;
struct TYPE_8__ {int /*<<< orphan*/  month; } ;
typedef  int /*<<< orphan*/  SYSTEMTIME ;
typedef  TYPE_2__ MONTHCAL_INFO ;
typedef  int INT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int MCS_MULTISELECT ; 
 scalar_t__ MONTHCAL_CompareMonths (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int MONTHCAL_GetCalCount (TYPE_2__*) ; 
 int /*<<< orphan*/  MONTHCAL_GetMonth (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  MONTHCAL_GetSelRange (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MONTHCAL_SetCurSel (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MONTHCAL_SetSelRange (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void MONTHCAL_Scroll(MONTHCAL_INFO *infoPtr, INT delta, BOOL keep_selection)
{
  INT i, selIdx = -1;

  for(i = 0; i < MONTHCAL_GetCalCount(infoPtr); i++)
  {
    /* save selection position to shift it later */
    if (selIdx == -1 && MONTHCAL_CompareMonths(&infoPtr->minSel, &infoPtr->calendars[i].month) == 0)
      selIdx = i;

    MONTHCAL_GetMonth(&infoPtr->calendars[i].month, delta);
  }

  if (keep_selection)
    return;

  /* selection is always shifted to first calendar */
  if (infoPtr->dwStyle & MCS_MULTISELECT)
  {
    SYSTEMTIME range[2];

    MONTHCAL_GetSelRange(infoPtr, range);
    MONTHCAL_GetMonth(&range[0], delta - selIdx);
    MONTHCAL_GetMonth(&range[1], delta - selIdx);
    MONTHCAL_SetSelRange(infoPtr, range);
  }
  else
  {
    SYSTEMTIME st = infoPtr->minSel;

    MONTHCAL_GetMonth(&st, delta - selIdx);
    MONTHCAL_SetCurSel(infoPtr, &st);
  }
}