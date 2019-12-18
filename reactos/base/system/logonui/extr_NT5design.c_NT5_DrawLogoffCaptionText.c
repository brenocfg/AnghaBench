#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_9__ {int cy; int cx; } ;
struct TYPE_8__ {int lfHeight; int lfWeight; int /*<<< orphan*/  lfFaceName; int /*<<< orphan*/  lfCharSet; } ;
struct TYPE_7__ {int top; int left; int right; scalar_t__ bottom; } ;
typedef  TYPE_1__ RECT ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  TYPE_2__ LOGFONTW ;
typedef  int /*<<< orphan*/  INT ;
typedef  scalar_t__ HFONT ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 scalar_t__ CreateFontIndirectW (TYPE_2__*) ; 
 int /*<<< orphan*/  DEFAULT_CHARSET ; 
 int DT_NOPREFIX ; 
 int DT_RIGHT ; 
 int DT_WORDBREAK ; 
 int /*<<< orphan*/  DeleteObject (scalar_t__) ; 
 int /*<<< orphan*/  DrawTextW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_1__*,int) ; 
 scalar_t__ GetDeviceCaps (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LF_FACESIZE ; 
 int /*<<< orphan*/  LOGPIXELSY ; 
 int /*<<< orphan*/  RGB (int,int,int) ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  SetBkMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetTextColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRANSPARENT ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_2__*,int) ; 
 TYPE_3__* g_pInfo ; 
 int /*<<< orphan*/  wcscpy_s (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static VOID
NT5_DrawLogoffCaptionText(LPWSTR lpText,
                          HDC hdcMem)
{
    HFONT hFont;
    LOGFONTW LogFont;
    RECT TextRect;
    INT PrevBkMode;

    /* Setup the font we'll use */
    ZeroMemory(&LogFont, sizeof(LOGFONTW));
    LogFont.lfCharSet = DEFAULT_CHARSET;
    LogFont.lfHeight = 22;
    LogFont.lfWeight = 109; // From WinXP disassembly
    wcscpy_s(LogFont.lfFaceName, LF_FACESIZE, L"Arial");

    /* Create it */
    hFont = CreateFontIndirectW(&LogFont);
    if (hFont)
    {
        /* Set the font and font colour */
        SelectObject(hdcMem, hFont);
        SetTextColor(hdcMem, RGB(255, 255, 255));

        /* Create the text rect */
        TextRect.top = (g_pInfo->cy / 2) + 34;
        TextRect.bottom = (g_pInfo->cy / 2) + 34 + (GetDeviceCaps(hdcMem, LOGPIXELSY));
        TextRect.left = g_pInfo->cx / 3;
        TextRect.right = (g_pInfo->cx / 2) + 35 + 137;

        /* Set the background mode to transparent */
        PrevBkMode = SetBkMode(hdcMem, TRANSPARENT);

        /* Draw the text to the mem DC */
        DrawTextW(hdcMem,
                  lpText,
                  -1,
                  &TextRect,
                  DT_NOPREFIX | DT_WORDBREAK | DT_RIGHT); // WinXP disassembly uses 0x812

        /* Set the previous background mode */
        SetBkMode(hdcMem, PrevBkMode);

        /* Delete the font */
        DeleteObject(hFont);
    }
}