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
typedef  char WCHAR ;
struct TYPE_4__ {int right; scalar_t__ bottom; scalar_t__ top; } ;
typedef  TYPE_1__ RECT ;
typedef  int LONG ;
typedef  int /*<<< orphan*/  HFONT ;
typedef  scalar_t__ HDC ;
typedef  int /*<<< orphan*/  HBITMAP ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BitBlt (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateCompatibleBitmap (scalar_t__,int,scalar_t__) ; 
 scalar_t__ CreateCompatibleDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateFontW (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DeleteDC (scalar_t__) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FillRect (scalar_t__,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDeviceCaps (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetStockObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOGPIXELSX ; 
 int /*<<< orphan*/  LineTo (scalar_t__,int,int) ; 
 int /*<<< orphan*/  MoveToEx (scalar_t__,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SRCAND ; 
 int /*<<< orphan*/  SelectObject (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetBkMode (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetTextAlign (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TA_CENTER ; 
 int /*<<< orphan*/  TRANSPARENT ; 
 int /*<<< orphan*/  TextOutW (scalar_t__,int,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WHITE_BRUSH ; 
 int /*<<< orphan*/  centmm_to_twips (int) ; 
 int /*<<< orphan*/  lstrlenW (char*) ; 
 int twips_to_pixels (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wsprintfW (char*,char*,int) ; 

__attribute__((used)) static void add_ruler_units(HDC hdcRuler, RECT* drawRect, BOOL NewMetrics, LONG EditLeftmost)
{
    static HDC hdc;

    if(NewMetrics)
    {
        static HBITMAP hBitmap;
        int i, x, y, RulerTextEnd;
        int CmPixels;
        int QuarterCmPixels;
        HFONT hFont;
        WCHAR FontName[] = {'M','S',' ','S','a','n','s',' ','S','e','r','i','f',0};

        if(hdc)
        {
            DeleteDC(hdc);
            DeleteObject(hBitmap);
        }

        hdc = CreateCompatibleDC(0);

        CmPixels = twips_to_pixels(centmm_to_twips(1000), GetDeviceCaps(hdc, LOGPIXELSX));
        QuarterCmPixels = (int)((float)CmPixels / 4.0);

        hBitmap = CreateCompatibleBitmap(hdc, drawRect->right, drawRect->bottom);
        SelectObject(hdc, hBitmap);
        FillRect(hdc, drawRect, GetStockObject(WHITE_BRUSH));

        hFont = CreateFontW(10, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, FontName);

        SelectObject(hdc, hFont);
        SetBkMode(hdc, TRANSPARENT);
        SetTextAlign(hdc, TA_CENTER);
        y = (int)(((float)drawRect->bottom - (float)drawRect->top) / 2.0) + 1;
        RulerTextEnd = drawRect->right - EditLeftmost + 1;
        for(i = 1, x = EditLeftmost; x < (drawRect->right - EditLeftmost + 1); i ++)
        {
            WCHAR str[3];
            WCHAR format[] = {'%','d',0};
            int x2 = x;

            x2 += QuarterCmPixels;
            if(x2 > RulerTextEnd)
                break;

            MoveToEx(hdc, x2, y, NULL);
            LineTo(hdc, x2, y+2);

            x2 += QuarterCmPixels;
            if(x2 > RulerTextEnd)
                break;

            MoveToEx(hdc, x2, y - 3, NULL);
            LineTo(hdc, x2, y + 3);

            x2 += QuarterCmPixels;
            if(x2 > RulerTextEnd)
                break;

            MoveToEx(hdc, x2, y, NULL);
            LineTo(hdc, x2, y+2);

            x += CmPixels;
            if(x > RulerTextEnd)
                break;

            wsprintfW(str, format, i);
            TextOutW(hdc, x, 5, str, lstrlenW(str));
        }
        DeleteObject(hFont);
    }

    BitBlt(hdcRuler, 0, 0, drawRect->right, drawRect->bottom, hdc, 0, 0, SRCAND);
}