#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lf ;
struct TYPE_9__ {int /*<<< orphan*/  fIcon; int /*<<< orphan*/ * hbmMask; int /*<<< orphan*/ * hbmColor; } ;
struct TYPE_8__ {int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
typedef  TYPE_1__ RECT ;
typedef  char* LPWSTR ;
typedef  int /*<<< orphan*/  LOGFONTW ;
typedef  int INT ;
typedef  TYPE_2__ ICONINFO ;
typedef  int /*<<< orphan*/ * HICON ;
typedef  int /*<<< orphan*/ * HFONT ;
typedef  scalar_t__ HDC ;
typedef  int /*<<< orphan*/ * HBITMAP ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BLACKNESS ; 
 int /*<<< orphan*/  COLOR_HIGHLIGHT ; 
 int /*<<< orphan*/  COLOR_HIGHLIGHTTEXT ; 
 int /*<<< orphan*/  COLOR_WINDOW ; 
 int /*<<< orphan*/  COLOR_WINDOWTEXT ; 
 int /*<<< orphan*/ * CreateBitmap (int,int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateCompatibleBitmap (scalar_t__,int,int) ; 
 scalar_t__ CreateCompatibleDC (scalar_t__) ; 
 int /*<<< orphan*/ * CreateFontIndirectW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateIconIndirect (TYPE_2__*) ; 
 int DT_CENTER ; 
 int DT_SINGLELINE ; 
 int DT_VCENTER ; 
 int /*<<< orphan*/  DeleteDC (scalar_t__) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DrawTextW (scalar_t__,char*,int,TYPE_1__*,int) ; 
 int /*<<< orphan*/  ETO_OPAQUE ; 
 int /*<<< orphan*/  ExtTextOutW (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FillRect (scalar_t__,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ GetDC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetSysColor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetSysColorBrush (int /*<<< orphan*/ ) ; 
 int GetSystemMetrics (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PatBlt (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  SM_CXSMICON ; 
 int /*<<< orphan*/  SM_CYSMICON ; 
 int /*<<< orphan*/  SPI_GETICONTITLELOGFONT ; 
 int /*<<< orphan*/ * SelectObject (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetBkColor (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetRect (TYPE_1__*,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SetTextColor (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ SystemParametersInfoW (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static HICON
CreateLayoutIcon(LPWSTR szLayout, BOOL bIsDefault)
{
    INT width = GetSystemMetrics(SM_CXSMICON) * 2;
    INT height = GetSystemMetrics(SM_CYSMICON);
    HDC hdc;
    HDC hdcsrc;
    HBITMAP hBitmap;
    HICON hIcon = NULL;

    hdcsrc = GetDC(NULL);
    hdc = CreateCompatibleDC(hdcsrc);
    hBitmap = CreateCompatibleBitmap(hdcsrc, width, height);

    ReleaseDC(NULL, hdcsrc);

    if (hdc && hBitmap)
    {
        HBITMAP hBmpNew;

        hBmpNew = CreateBitmap(width, height, 1, 1, NULL);
        if (hBmpNew)
        {
            LOGFONTW lf;

            if (SystemParametersInfoW(SPI_GETICONTITLELOGFONT, sizeof(lf), &lf, 0))
            {
                ICONINFO IconInfo;
                HFONT hFont;

                hFont = CreateFontIndirectW(&lf);

                if (hFont != NULL)
                {
                    HBITMAP hBmpOld;

                    hBmpOld = SelectObject(hdc, hBitmap);

                    if (hBmpOld != NULL)
                    {
                        RECT rect;

                        SetRect(&rect, 0, 0, width / 2, height);

                        if (bIsDefault != FALSE)
                        {
                            SetBkColor(hdc, GetSysColor(COLOR_WINDOW));
                            SetTextColor(hdc, GetSysColor(COLOR_WINDOWTEXT));

                            ExtTextOutW(hdc, rect.left, rect.top, ETO_OPAQUE, &rect, L"", 0, NULL);

                            SelectObject(hdc, hFont);
                            DrawTextW(hdc, L"\x2022", 1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
                        }
                        else
                        {
                            FillRect(hdc, &rect, GetSysColorBrush(COLOR_WINDOW));
                        }

                        SetRect(&rect, width / 2, 0, width, height);

                        SetBkColor(hdc, GetSysColor(COLOR_HIGHLIGHT));
                        SetTextColor(hdc, GetSysColor(COLOR_HIGHLIGHTTEXT));

                        ExtTextOutW(hdc, rect.left, rect.top, ETO_OPAQUE, &rect, L"", 0, NULL);

                        SelectObject(hdc, hFont);
                        DrawTextW(hdc, szLayout, 2, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

                        SelectObject(hdc, hBmpNew);

                        PatBlt(hdc, 0, 0, width, height, BLACKNESS);

                        SelectObject(hdc, hBmpOld);

                        IconInfo.hbmColor = hBitmap;
                        IconInfo.hbmMask = hBmpNew;
                        IconInfo.fIcon = TRUE;

                        hIcon = CreateIconIndirect(&IconInfo);

                        DeleteObject(hBmpOld);
                    }

                    DeleteObject(hFont);
                }
            }

            DeleteObject(hBmpNew);
        }
    }

    DeleteDC(hdc);
    DeleteObject(hBitmap);

    return hIcon;
}