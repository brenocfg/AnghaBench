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
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_4__ {int firstDay; int /*<<< orphan*/  hwndSelf; void* firstDaySet; } ;
typedef  TYPE_1__ MONTHCAL_INFO ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int INT ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 void* FALSE ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int /*<<< orphan*/  GetLocaleInfoW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  LOCALE_IFIRSTDAYOFWEEK ; 
 int /*<<< orphan*/  LOCALE_USER_DEFAULT ; 
 int /*<<< orphan*/  MONTHCAL_GetFirstDayOfWeek (TYPE_1__*) ; 
 int /*<<< orphan*/  TRACE (char*,int,...) ; 
 void* TRUE ; 
 int atoiW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlenW (int /*<<< orphan*/ *) ; 

__attribute__((used)) static LRESULT
MONTHCAL_SetFirstDayOfWeek(MONTHCAL_INFO *infoPtr, INT day)
{
  LRESULT prev = MONTHCAL_GetFirstDayOfWeek(infoPtr);
  int new_day;

  TRACE("%d\n", day);

  if(day == -1)
  {
    WCHAR buf[80];

    GetLocaleInfoW(LOCALE_USER_DEFAULT, LOCALE_IFIRSTDAYOFWEEK, buf, ARRAY_SIZE(buf));
    TRACE("%s %d\n", debugstr_w(buf), strlenW(buf));

    new_day = atoiW(buf);

    infoPtr->firstDaySet = FALSE;
  }
  else if(day >= 7)
  {
    new_day = 6; /* max first day allowed */
    infoPtr->firstDaySet = TRUE;
  }
  else
  {
    /* Native behaviour for that case is broken: invalid date number >31
       got displayed at (0,0) position, current month starts always from
       (1,0) position. Should be implemented here as well only if there's
       nothing else to do. */
    if (day < -1)
      FIXME("No bug compatibility for day=%d\n", day);

    new_day = day;
    infoPtr->firstDaySet = TRUE;
  }

  /* convert from locale to SYSTEMTIME format */
  infoPtr->firstDay = (new_day >= 0) ? (++new_day) % 7 : new_day;

  InvalidateRect(infoPtr->hwndSelf, NULL, FALSE);

  return prev;
}