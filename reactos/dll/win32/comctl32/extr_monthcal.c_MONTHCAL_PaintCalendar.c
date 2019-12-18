#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int UINT ;
struct TYPE_16__ {scalar_t__ top; scalar_t__ bottom; } ;
struct TYPE_23__ {size_t firstDay; int* monthdayState; int /*<<< orphan*/ * colors; scalar_t__ width_increment; TYPE_5__* calendars; int /*<<< orphan*/  hFont; scalar_t__ textHeight; int /*<<< orphan*/ * pens; int /*<<< orphan*/ * brushes; TYPE_1__ todayrect; } ;
struct TYPE_22__ {scalar_t__ left; scalar_t__ right; scalar_t__ bottom; } ;
struct TYPE_21__ {int wDay; int /*<<< orphan*/  wYear; int /*<<< orphan*/  wMonth; } ;
struct TYPE_19__ {scalar_t__ right; } ;
struct TYPE_18__ {scalar_t__ left; scalar_t__ right; scalar_t__ bottom; } ;
struct TYPE_17__ {scalar_t__ bottom; } ;
struct TYPE_20__ {TYPE_7__ wdays; TYPE_4__ weeknums; TYPE_3__ days; TYPE_2__ title; TYPE_6__ month; } ;
typedef  TYPE_6__ SYSTEMTIME ;
typedef  TYPE_7__ RECT ;
typedef  int /*<<< orphan*/  PAINTSTRUCT ;
typedef  TYPE_8__ MONTHCAL_INFO ;
typedef  size_t INT ;
typedef  int /*<<< orphan*/  HPEN ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 size_t BrushMonth ; 
 int DT_CENTER ; 
 int DT_SINGLELINE ; 
 int DT_VCENTER ; 
 int /*<<< orphan*/  DrawTextW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_7__*,int) ; 
 int /*<<< orphan*/  FillRect (int /*<<< orphan*/ ,TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LineTo (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 size_t MCSC_MONTHBK ; 
 size_t MCSC_TEXT ; 
 size_t MCSC_TITLEBK ; 
 int /*<<< orphan*/  MONTHCAL_DrawDay (TYPE_8__ const*,int /*<<< orphan*/ ,TYPE_6__*,int,int /*<<< orphan*/  const*) ; 
 int MONTHCAL_MonthLength (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MoveToEx (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OffsetRect (TYPE_7__*,scalar_t__,int /*<<< orphan*/ ) ; 
 size_t PenText ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetBkColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetTextColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_localized_dayname (TYPE_8__ const*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlenW (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void MONTHCAL_PaintCalendar(const MONTHCAL_INFO *infoPtr, HDC hdc, const PAINTSTRUCT *ps, INT calIdx)
{
  const SYSTEMTIME *date = &infoPtr->calendars[calIdx].month;
  INT i, j;
  UINT length;
  RECT r, fill_bk_rect;
  SYSTEMTIME st;
  WCHAR buf[80];
  HPEN old_pen;
  int mask;

  /* fill whole days area - from week days area to today note rectangle */
  fill_bk_rect = infoPtr->calendars[calIdx].wdays;
  fill_bk_rect.bottom = infoPtr->calendars[calIdx].days.bottom +
                          (infoPtr->todayrect.bottom - infoPtr->todayrect.top);

  FillRect(hdc, &fill_bk_rect, infoPtr->brushes[BrushMonth]);

  /* draw line under day abbreviations */
  old_pen = SelectObject(hdc, infoPtr->pens[PenText]);
  MoveToEx(hdc, infoPtr->calendars[calIdx].days.left + 3,
                infoPtr->calendars[calIdx].title.bottom + infoPtr->textHeight + 1, NULL);
  LineTo(hdc, infoPtr->calendars[calIdx].days.right - 3,
              infoPtr->calendars[calIdx].title.bottom + infoPtr->textHeight + 1);
  SelectObject(hdc, old_pen);

  infoPtr->calendars[calIdx].wdays.left = infoPtr->calendars[calIdx].days.left =
      infoPtr->calendars[calIdx].weeknums.right;

  /* draw day abbreviations */
  SelectObject(hdc, infoPtr->hFont);
  SetBkColor(hdc, infoPtr->colors[MCSC_MONTHBK]);
  SetTextColor(hdc, infoPtr->colors[MCSC_TITLEBK]);
  /* rectangle to draw a single day abbreviation within */
  r = infoPtr->calendars[calIdx].wdays;
  r.right = r.left + infoPtr->width_increment;

  i = infoPtr->firstDay;
  for(j = 0; j < 7; j++) {
    get_localized_dayname(infoPtr, (i + j + 6) % 7, buf, ARRAY_SIZE(buf));
    DrawTextW(hdc, buf, strlenW(buf), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    OffsetRect(&r, infoPtr->width_increment, 0);
  }

  /* draw current month */
  SetTextColor(hdc, infoPtr->colors[MCSC_TEXT]);
  st = *date;
  st.wDay = 1;
  mask = 1;
  length = MONTHCAL_MonthLength(date->wMonth, date->wYear);
  while(st.wDay <= length)
  {
    MONTHCAL_DrawDay(infoPtr, hdc, &st, infoPtr->monthdayState[calIdx+1] & mask, ps);
    mask <<= 1;
    st.wDay++;
  }
}