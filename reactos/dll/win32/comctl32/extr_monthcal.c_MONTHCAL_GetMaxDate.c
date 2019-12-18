#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int firstDay; TYPE_1__* calendars; } ;
struct TYPE_11__ {int wDay; int /*<<< orphan*/  wYear; int /*<<< orphan*/  wMonth; } ;
struct TYPE_10__ {TYPE_2__ month; } ;
typedef  TYPE_2__ SYSTEMTIME ;
typedef  TYPE_3__ MONTHCAL_INFO ;
typedef  int INT ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int MONTHCAL_CalculateDayOfWeek (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int MONTHCAL_GetCalCount (TYPE_3__ const*) ; 
 int /*<<< orphan*/  MONTHCAL_GetNextMonth (TYPE_2__*) ; 
 int /*<<< orphan*/  MONTHCAL_GetPrevMonth (TYPE_2__*) ; 
 int MONTHCAL_MonthLength (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static void MONTHCAL_GetMaxDate(const MONTHCAL_INFO *infoPtr, SYSTEMTIME *date)
{
  /* the latest date is in latest calendar */
  SYSTEMTIME st, *lt_month = &infoPtr->calendars[MONTHCAL_GetCalCount(infoPtr)-1].month;
  INT first_day;

  *date = *lt_month;
  st = *lt_month;

  /* day of week of first day of current month */
  st.wDay = 1;
  first_day = MONTHCAL_CalculateDayOfWeek(&st, FALSE);

  MONTHCAL_GetNextMonth(date);
  MONTHCAL_GetPrevMonth(&st);

  /* last calendar starts with some date from previous month that not displayed */
  st.wDay = MONTHCAL_MonthLength(st.wMonth, st.wYear) +
             (infoPtr->firstDay - first_day) % 7 + 1;
  if (st.wDay > MONTHCAL_MonthLength(st.wMonth, st.wYear)) st.wDay -= 7;

  /* Use month length to get max day. 42 means max day count in calendar area */
  date->wDay = 42 - (MONTHCAL_MonthLength(st.wMonth, st.wYear) - st.wDay + 1) -
                     MONTHCAL_MonthLength(lt_month->wMonth, lt_month->wYear);

  /* fix day of week */
  MONTHCAL_CalculateDayOfWeek(date, TRUE);
}