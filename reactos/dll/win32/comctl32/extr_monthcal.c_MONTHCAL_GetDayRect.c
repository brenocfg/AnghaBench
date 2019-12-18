#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* calendars; } ;
struct TYPE_7__ {int /*<<< orphan*/  month; } ;
typedef  int /*<<< orphan*/  SYSTEMTIME ;
typedef  int /*<<< orphan*/  RECT ;
typedef  TYPE_2__ MONTHCAL_INFO ;
typedef  int INT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ MONTHCAL_CompareMonths (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int MONTHCAL_GetCalCount (TYPE_2__ const*) ; 
 int /*<<< orphan*/  MONTHCAL_GetDayPos (TYPE_2__ const*,int /*<<< orphan*/  const*,int*,int*,int) ; 
 int /*<<< orphan*/  MONTHCAL_GetDayRectI (TYPE_2__ const*,int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  MONTHCAL_ValidateDate (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  SetRectEmpty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL MONTHCAL_GetDayRect(const MONTHCAL_INFO *infoPtr, const SYSTEMTIME *date, RECT *r, INT calIdx)
{
  INT col, row;

  if (!MONTHCAL_ValidateDate(date))
  {
      SetRectEmpty(r);
      return FALSE;
  }

  if (calIdx == -1)
  {
      INT cmp = MONTHCAL_CompareMonths(date, &infoPtr->calendars[0].month);

      if (cmp <= 0)
          calIdx = 0;
      else
      {
          cmp = MONTHCAL_CompareMonths(date, &infoPtr->calendars[MONTHCAL_GetCalCount(infoPtr)-1].month);
          if (cmp >= 0)
              calIdx = MONTHCAL_GetCalCount(infoPtr)-1;
          else
          {
              for (calIdx = 1; calIdx < MONTHCAL_GetCalCount(infoPtr)-1; calIdx++)
                  if (MONTHCAL_CompareMonths(date, &infoPtr->calendars[calIdx].month) == 0)
                      break;
          }
      }
  }

  MONTHCAL_GetDayPos(infoPtr, date, &col, &row, calIdx);
  MONTHCAL_GetDayRectI(infoPtr, r, col, row, calIdx);

  return TRUE;
}