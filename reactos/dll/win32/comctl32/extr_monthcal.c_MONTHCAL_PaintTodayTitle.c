#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
struct TYPE_6__ {int cx; int cy; } ;
struct TYPE_7__ {int dwStyle; int /*<<< orphan*/  width_increment; int /*<<< orphan*/ * colors; int /*<<< orphan*/  hBoldFont; int /*<<< orphan*/  todaysDate; TYPE_1__ dim; } ;
typedef  int /*<<< orphan*/  RECT ;
typedef  int /*<<< orphan*/  PAINTSTRUCT ;
typedef  TYPE_2__ MONTHCAL_INFO ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HFONT ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (char*) ; 
 int /*<<< orphan*/  COMCTL32_hModule ; 
 int /*<<< orphan*/  DATE_SHORTDATE ; 
 int DT_CALCRECT ; 
 int DT_LEFT ; 
 int DT_SINGLELINE ; 
 int DT_VCENTER ; 
 int /*<<< orphan*/  DrawTextW (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  GetDateFormatW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDM_TODAY ; 
 int /*<<< orphan*/  LOCALE_USER_DEFAULT ; 
 int /*<<< orphan*/  LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 size_t MCSC_TEXT ; 
 int MCS_NOTODAY ; 
 int MCS_NOTODAYCIRCLE ; 
 int MCS_WEEKNUMBERS ; 
 int /*<<< orphan*/  MONTHCAL_Circle (TYPE_2__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MONTHCAL_GetDayRectI (TYPE_2__ const*,int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  OffsetRect (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetTextColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wsprintfW (char*,char const*,char*,char*) ; 

__attribute__((used)) static void MONTHCAL_PaintTodayTitle(const MONTHCAL_INFO *infoPtr, HDC hdc, const PAINTSTRUCT *ps)
{
  static const WCHAR fmt_todayW[] = { '%','s',' ','%','s',0 };
  WCHAR buf_todayW[30], buf_dateW[20], buf[80];
  RECT text_rect, box_rect;
  HFONT old_font;
  INT col;

  if(infoPtr->dwStyle & MCS_NOTODAY) return;

  LoadStringW(COMCTL32_hModule, IDM_TODAY, buf_todayW, ARRAY_SIZE(buf_todayW));
  col = infoPtr->dwStyle & MCS_NOTODAYCIRCLE ? 0 : 1;
  if (infoPtr->dwStyle & MCS_WEEKNUMBERS) col--;
  /* label is located below first calendar last row */
  MONTHCAL_GetDayRectI(infoPtr, &text_rect, col, 6, infoPtr->dim.cx * infoPtr->dim.cy - infoPtr->dim.cx);
  box_rect = text_rect;

  GetDateFormatW(LOCALE_USER_DEFAULT, DATE_SHORTDATE, &infoPtr->todaysDate, NULL, buf_dateW, ARRAY_SIZE(buf_dateW));
  old_font = SelectObject(hdc, infoPtr->hBoldFont);
  SetTextColor(hdc, infoPtr->colors[MCSC_TEXT]);

  wsprintfW(buf, fmt_todayW, buf_todayW, buf_dateW);
  DrawTextW(hdc, buf, -1, &text_rect, DT_CALCRECT | DT_LEFT | DT_VCENTER | DT_SINGLELINE);
  DrawTextW(hdc, buf, -1, &text_rect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);

  if(!(infoPtr->dwStyle & MCS_NOTODAYCIRCLE)) {
    OffsetRect(&box_rect, -infoPtr->width_increment, 0);
    MONTHCAL_Circle(infoPtr, hdc, &box_rect);
  }

  SelectObject(hdc, old_font);
}