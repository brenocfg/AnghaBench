#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct TYPE_24__ {int /*<<< orphan*/  clrWindowText; } ;
struct TYPE_23__ {int /*<<< orphan*/  todayrect; TYPE_1__* calendars; } ;
struct TYPE_22__ {int /*<<< orphan*/  rcPaint; } ;
struct TYPE_21__ {int /*<<< orphan*/  wdays; int /*<<< orphan*/  title; } ;
typedef  int /*<<< orphan*/  RECT ;
typedef  TYPE_2__ PAINTSTRUCT ;
typedef  TYPE_3__ MONTHCAL_INFO ;
typedef  size_t INT ;
typedef  int /*<<< orphan*/  HFONT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  COLORREF ;

/* Variables and functions */
 int /*<<< orphan*/  DIRECTION_BACKWARD ; 
 int /*<<< orphan*/  DIRECTION_FORWARD ; 
 int /*<<< orphan*/  GetBkColor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetCurrentObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IntersectRect (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t MONTHCAL_GetCalCount (TYPE_3__*) ; 
 int /*<<< orphan*/  MONTHCAL_PaintButton (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MONTHCAL_PaintCalendar (TYPE_3__*,int /*<<< orphan*/ ,TYPE_2__ const*,size_t) ; 
 int /*<<< orphan*/  MONTHCAL_PaintFocusAndCircle (TYPE_3__*,int /*<<< orphan*/ ,TYPE_2__ const*) ; 
 int /*<<< orphan*/  MONTHCAL_PaintLeadTrailMonths (TYPE_3__*,int /*<<< orphan*/ ,TYPE_2__ const*) ; 
 int /*<<< orphan*/  MONTHCAL_PaintTitle (TYPE_3__*,int /*<<< orphan*/ ,TYPE_2__ const*,size_t) ; 
 int /*<<< orphan*/  MONTHCAL_PaintTodayTitle (TYPE_3__*,int /*<<< orphan*/ ,TYPE_2__ const*) ; 
 int /*<<< orphan*/  MONTHCAL_PaintWeeknumbers (TYPE_3__*,int /*<<< orphan*/ ,TYPE_2__ const*,size_t) ; 
 int /*<<< orphan*/  OBJ_FONT ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetBkColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetTextColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnionRect (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__ comctl32_color ; 

__attribute__((used)) static void MONTHCAL_Refresh(MONTHCAL_INFO *infoPtr, HDC hdc, const PAINTSTRUCT *ps)
{
  COLORREF old_text_clr, old_bk_clr;
  HFONT old_font;
  INT i;

  old_text_clr = SetTextColor(hdc, comctl32_color.clrWindowText);
  old_bk_clr   = GetBkColor(hdc);
  old_font     = GetCurrentObject(hdc, OBJ_FONT);

  for (i = 0; i < MONTHCAL_GetCalCount(infoPtr); i++)
  {
    RECT *title = &infoPtr->calendars[i].title;
    RECT r;

    /* draw title, redraw all its elements */
    if (IntersectRect(&r, &(ps->rcPaint), title))
        MONTHCAL_PaintTitle(infoPtr, hdc, ps, i);

    /* draw calendar area */
    UnionRect(&r, &infoPtr->calendars[i].wdays, &infoPtr->todayrect);
    if (IntersectRect(&r, &(ps->rcPaint), &r))
        MONTHCAL_PaintCalendar(infoPtr, hdc, ps, i);

    /* week numbers */
    MONTHCAL_PaintWeeknumbers(infoPtr, hdc, ps, i);
  }

  /* partially visible months */
  MONTHCAL_PaintLeadTrailMonths(infoPtr, hdc, ps);

  /* focus and today rectangle */
  MONTHCAL_PaintFocusAndCircle(infoPtr, hdc, ps);

  /* today at the bottom left */
  MONTHCAL_PaintTodayTitle(infoPtr, hdc, ps);

  /* navigation buttons */
  MONTHCAL_PaintButton(infoPtr, hdc, DIRECTION_BACKWARD);
  MONTHCAL_PaintButton(infoPtr, hdc, DIRECTION_FORWARD);

  /* restore context */
  SetBkColor(hdc, old_bk_clr);
  SelectObject(hdc, old_font);
  SetTextColor(hdc, old_text_clr);
}