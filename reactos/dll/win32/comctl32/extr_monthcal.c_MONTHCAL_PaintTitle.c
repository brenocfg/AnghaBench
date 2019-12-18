#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
struct TYPE_17__ {int left; int right; } ;
struct TYPE_16__ {TYPE_1__* calendars; int /*<<< orphan*/  hBoldFont; int /*<<< orphan*/ * colors; int /*<<< orphan*/ * brushes; } ;
struct TYPE_15__ {int right; int left; } ;
struct TYPE_14__ {int cx; } ;
struct TYPE_13__ {scalar_t__ wMonth; scalar_t__ wYear; } ;
struct TYPE_12__ {TYPE_6__ titlemonth; TYPE_6__ titleyear; TYPE_2__ month; TYPE_4__ title; } ;
typedef  TYPE_2__ SYSTEMTIME ;
typedef  TYPE_3__ SIZE ;
typedef  TYPE_4__ RECT ;
typedef  int /*<<< orphan*/  PAINTSTRUCT ;
typedef  TYPE_5__ MONTHCAL_INFO ;
typedef  size_t INT ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (char*) ; 
 size_t BrushTitle ; 
 int /*<<< orphan*/  DATE_YEARMONTH ; 
 int DT_CENTER ; 
 int DT_SINGLELINE ; 
 int DT_VCENTER ; 
 int /*<<< orphan*/  DrawTextW (int /*<<< orphan*/ ,char*,int,TYPE_4__*,int) ; 
 int /*<<< orphan*/  FillRect (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDateFormatW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__ const*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetLocaleInfoW (int /*<<< orphan*/ ,scalar_t__,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetTextExtentPoint32W (int /*<<< orphan*/ ,char*,int,TYPE_3__*) ; 
 scalar_t__ LOCALE_SABBREVMONTHNAME1 ; 
 scalar_t__ LOCALE_SMONTHNAME1 ; 
 scalar_t__ LOCALE_SYEARMONTH ; 
 int /*<<< orphan*/  LOCALE_USER_DEFAULT ; 
 size_t MCSC_TITLEBK ; 
 size_t MCSC_TITLETEXT ; 
 int /*<<< orphan*/  OffsetRect (TYPE_6__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetBkColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetTextColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlenW (char*) ; 
 int /*<<< orphan*/  strncmpW (char*,char*,int) ; 
 scalar_t__ strstrW (char*,char const*) ; 
 int /*<<< orphan*/  wsprintfW (char*,char const*,scalar_t__) ; 

__attribute__((used)) static void MONTHCAL_PaintTitle(MONTHCAL_INFO *infoPtr, HDC hdc, const PAINTSTRUCT *ps, INT calIdx)
{
  static const WCHAR mmmmW[] = {'M','M','M','M',0};
  static const WCHAR mmmW[] = {'M','M','M',0};
  static const WCHAR mmW[] = {'M','M',0};
  static const WCHAR fmtyearW[] = {'%','l','d',0};
  static const WCHAR fmtmmW[] = {'%','0','2','d',0};
  static const WCHAR fmtmW[] = {'%','d',0};
  RECT *title = &infoPtr->calendars[calIdx].title;
  const SYSTEMTIME *st = &infoPtr->calendars[calIdx].month;
  WCHAR monthW[80], strW[80], fmtW[80], yearW[6] /* valid year range is 1601-30827 */;
  int yearoffset, monthoffset, shiftX;
  SIZE sz;

  /* fill header box */
  FillRect(hdc, title, infoPtr->brushes[BrushTitle]);

  /* month/year string */
  SetBkColor(hdc, infoPtr->colors[MCSC_TITLEBK]);
  SetTextColor(hdc, infoPtr->colors[MCSC_TITLETEXT]);
  SelectObject(hdc, infoPtr->hBoldFont);

  /* draw formatted date string */
  GetDateFormatW(LOCALE_USER_DEFAULT, DATE_YEARMONTH, st, NULL, strW, ARRAY_SIZE(strW));
  DrawTextW(hdc, strW, strlenW(strW), title, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

  GetLocaleInfoW(LOCALE_USER_DEFAULT, LOCALE_SYEARMONTH, fmtW, ARRAY_SIZE(fmtW));
  wsprintfW(yearW, fmtyearW, st->wYear);

  /* month is trickier as it's possible to have different format pictures, we'll
     test for M, MM, MMM, and MMMM */
  if (strstrW(fmtW, mmmmW))
    GetLocaleInfoW(LOCALE_USER_DEFAULT, LOCALE_SMONTHNAME1+st->wMonth-1, monthW, ARRAY_SIZE(monthW));
  else if (strstrW(fmtW, mmmW))
    GetLocaleInfoW(LOCALE_USER_DEFAULT, LOCALE_SABBREVMONTHNAME1+st->wMonth-1, monthW, ARRAY_SIZE(monthW));
  else if (strstrW(fmtW, mmW))
    wsprintfW(monthW, fmtmmW, st->wMonth);
  else
    wsprintfW(monthW, fmtmW, st->wMonth);

  /* update hit boxes */
  yearoffset = 0;
  while (strW[yearoffset])
  {
    if (!strncmpW(&strW[yearoffset], yearW, strlenW(yearW)))
        break;
    yearoffset++;
  }

  monthoffset = 0;
  while (strW[monthoffset])
  {
    if (!strncmpW(&strW[monthoffset], monthW, strlenW(monthW)))
        break;
    monthoffset++;
  }

  /* for left limits use offsets */
  sz.cx = 0;
  if (yearoffset)
    GetTextExtentPoint32W(hdc, strW, yearoffset, &sz);
  infoPtr->calendars[calIdx].titleyear.left = sz.cx;

  sz.cx = 0;
  if (monthoffset)
    GetTextExtentPoint32W(hdc, strW, monthoffset, &sz);
  infoPtr->calendars[calIdx].titlemonth.left = sz.cx;

  /* for right limits use actual string parts lengths */
  GetTextExtentPoint32W(hdc, &strW[yearoffset], strlenW(yearW), &sz);
  infoPtr->calendars[calIdx].titleyear.right = infoPtr->calendars[calIdx].titleyear.left + sz.cx;

  GetTextExtentPoint32W(hdc, monthW, strlenW(monthW), &sz);
  infoPtr->calendars[calIdx].titlemonth.right = infoPtr->calendars[calIdx].titlemonth.left + sz.cx;

  /* Finally translate rectangles to match center aligned string,
     hit rectangles are relative to title rectangle before translation. */
  GetTextExtentPoint32W(hdc, strW, strlenW(strW), &sz);
  shiftX = (title->right - title->left - sz.cx) / 2 + title->left;
  OffsetRect(&infoPtr->calendars[calIdx].titleyear, shiftX, 0);
  OffsetRect(&infoPtr->calendars[calIdx].titlemonth, shiftX, 0);
}