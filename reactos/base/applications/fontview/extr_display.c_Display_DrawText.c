#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_6__ {char* szTypeFaceName; char** nSizes; int /*<<< orphan*/  hSizeFont; int /*<<< orphan*/ * szString; int /*<<< orphan*/ * hFonts; int /*<<< orphan*/  hCharSetFont; int /*<<< orphan*/  szFormat; int /*<<< orphan*/  hCaptionFont; } ;
struct TYPE_5__ {int tmDescent; scalar_t__ tmHeight; } ;
typedef  TYPE_1__ TEXTMETRIC ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  HFONT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  TYPE_2__ DISPLAYDATA ;

/* Variables and functions */
 int /*<<< orphan*/  BLACK_PEN ; 
 int /*<<< orphan*/  GetStockObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetTextMetrics (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  LF_FULLFACESIZE ; 
 int /*<<< orphan*/  LineTo (int /*<<< orphan*/ ,int,int) ; 
 int MAX_SIZES ; 
 int /*<<< orphan*/  MoveToEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ SPACING1 ; 
 scalar_t__ SPACING2 ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TextOutW (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swprintf (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ wcslen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
Display_DrawText(HDC hDC, DISPLAYDATA* pData, int nYPos)
{
	HFONT hOldFont;
	TEXTMETRIC tm;
	int i, y;
	WCHAR szSize[5];
	WCHAR szCaption[LF_FULLFACESIZE + 20];

	/* This is the location on the DC where we draw */
	y = -nYPos;

	hOldFont = SelectObject(hDC, pData->hCaptionFont);
	GetTextMetrics(hDC, &tm);

	swprintf(szCaption, L"%s%s", pData->szTypeFaceName, pData->szFormat);
	TextOutW(hDC, 0, y, szCaption, (INT)wcslen(szCaption));
	y += tm.tmHeight + SPACING1;

	/* Draw a separation Line */
	SelectObject(hDC, GetStockObject(BLACK_PEN));
	MoveToEx(hDC, 0, y, NULL);
	LineTo(hDC, 10000, y);
	y += SPACING2;

	/* TODO: Output font info */

	/* Output Character set */
	SelectObject(hDC, pData->hCharSetFont);
	GetTextMetrics(hDC, &tm);
	swprintf(szCaption, L"abcdefghijklmnopqrstuvwxyz");
	TextOutW(hDC, 0, y, szCaption, (INT)wcslen(szCaption));
	y += tm.tmHeight + 1;

	swprintf(szCaption, L"ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	TextOutW(hDC, 0, y, szCaption, (INT)wcslen(szCaption));
	y += tm.tmHeight + 1;

	swprintf(szCaption, L"0123456789.:,;(\"~!@#$%%^&*')");
	TextOutW(hDC, 0, y, szCaption, (INT)wcslen(szCaption));
	y += tm.tmHeight + 1;

	/* Draw a separation Line */
	SelectObject(hDC, GetStockObject(BLACK_PEN));
	MoveToEx(hDC, 0, y, NULL);
	LineTo(hDC, 10000, y);
	y += SPACING2;

	/* Output the strings for different sizes */
	for (i = 0; i < MAX_SIZES; i++)
	{
		SelectObject(hDC, pData->hFonts[i]);
		TextOutW(hDC, 20, y, pData->szString, (INT)wcslen(pData->szString));
		GetTextMetrics(hDC, &tm);
		y += tm.tmHeight + 1;
		SelectObject(hDC, pData->hSizeFont);
		swprintf(szSize, L"%d", pData->nSizes[i]);
		TextOutW(hDC, 0, y - 13 - tm.tmDescent, szSize, (INT)wcslen(szSize));
	}
	SelectObject(hDC, hOldFont);

	return y;
}