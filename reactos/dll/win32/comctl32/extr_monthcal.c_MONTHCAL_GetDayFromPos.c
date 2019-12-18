#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int width_increment; int height_increment; int firstDay; TYPE_2__* calendars; int /*<<< orphan*/  hwndSelf; } ;
struct TYPE_15__ {scalar_t__ x; int y; } ;
struct TYPE_14__ {scalar_t__ right; } ;
struct TYPE_13__ {int wDay; } ;
struct TYPE_11__ {int left; int top; } ;
struct TYPE_12__ {TYPE_1__ days; TYPE_3__ month; } ;
typedef  TYPE_3__ SYSTEMTIME ;
typedef  TYPE_4__ RECT ;
typedef  TYPE_5__ POINT ;
typedef  TYPE_6__ MONTHCAL_INFO ;
typedef  size_t INT ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int MONTHCAL_CalculateDayOfWeek (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int MONTHCAL_GetDayFromPos(const MONTHCAL_INFO *infoPtr, POINT pt, INT calIdx)
{
  SYSTEMTIME st = infoPtr->calendars[calIdx].month;
  int firstDay, col, row;
  RECT client;

  GetClientRect(infoPtr->hwndSelf, &client);

  /* if the point is outside the x bounds of the window put it at the boundary */
  if (pt.x > client.right) pt.x = client.right;

  col = (pt.x - infoPtr->calendars[calIdx].days.left ) / infoPtr->width_increment;
  row = (pt.y - infoPtr->calendars[calIdx].days.top  ) / infoPtr->height_increment;

  st.wDay = 1;
  firstDay = (MONTHCAL_CalculateDayOfWeek(&st, FALSE) + 6 - infoPtr->firstDay) % 7;
  return col + 7 * row - firstDay;
}