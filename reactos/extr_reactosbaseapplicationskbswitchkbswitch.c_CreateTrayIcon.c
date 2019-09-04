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
struct TYPE_7__ {int /*<<< orphan*/  fIcon; void* hbmMask; void* hbmColor; } ;
struct TYPE_6__ {int right; int bottom; scalar_t__ top; scalar_t__ left; } ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  TYPE_1__ RECT ;
typedef  int /*<<< orphan*/  LPTSTR ;
typedef  scalar_t__ LANGID ;
typedef  TYPE_2__ ICONINFO ;
typedef  int /*<<< orphan*/ * HICON ;
typedef  void* HFONT ;
typedef  scalar_t__ HDC ;
typedef  void* HBITMAP ;

/* Variables and functions */
 int /*<<< orphan*/  ANSI_CHARSET ; 
 int /*<<< orphan*/  ARRAYSIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BLACKNESS ; 
 int /*<<< orphan*/  CLIP_DEFAULT_PRECIS ; 
 int /*<<< orphan*/  COLOR_HIGHLIGHT ; 
 int /*<<< orphan*/  COLOR_HIGHLIGHTTEXT ; 
 void* CreateBitmap (int,int,int,int,int /*<<< orphan*/ *) ; 
 void* CreateCompatibleBitmap (scalar_t__,int,int) ; 
 scalar_t__ CreateCompatibleDC (scalar_t__) ; 
 void* CreateFont (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CreateIconIndirect (TYPE_2__*) ; 
 int /*<<< orphan*/  DEFAULT_QUALITY ; 
 int DT_CENTER ; 
 int DT_SINGLELINE ; 
 int DT_VCENTER ; 
 int /*<<< orphan*/  DeleteDC (scalar_t__) ; 
 int /*<<< orphan*/  DeleteObject (void*) ; 
 int /*<<< orphan*/  DrawText (scalar_t__,int /*<<< orphan*/ ,int,TYPE_1__*,int) ; 
 int /*<<< orphan*/  ETO_OPAQUE ; 
 int /*<<< orphan*/  ExtTextOut (scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FF_DONTCARE ; 
 int /*<<< orphan*/  FW_NORMAL ; 
 scalar_t__ GetDC (int /*<<< orphan*/ *) ; 
 scalar_t__ GetLocaleInfo (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetSysColor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOCALE_SISO639LANGNAME ; 
 int /*<<< orphan*/  OUT_DEFAULT_PRECIS ; 
 int /*<<< orphan*/  PatBlt (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ *,scalar_t__) ; 
 void* SelectObject (scalar_t__,void*) ; 
 int /*<<< orphan*/  SetBkColor (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetTextColor (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StringCchCopy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _T (char*) ; 
 scalar_t__ _tcstoul (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  _tcsupr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HICON
CreateTrayIcon(LPTSTR szLCID)
{
    LANGID lId;
    TCHAR szBuf[3];
    HDC hdc, hdcsrc;
    HBITMAP hBitmap, hBmpNew, hBmpOld;
    RECT rect;
    HFONT hFontOld, hFont = NULL;
    ICONINFO IconInfo;
    HICON hIcon = NULL;

    lId = (LANGID)_tcstoul(szLCID, NULL, 16);
    if (GetLocaleInfo(lId,
                      LOCALE_SISO639LANGNAME,
                      szBuf,
                      ARRAYSIZE(szBuf)) == 0)
    {
        StringCchCopy(szBuf, ARRAYSIZE(szBuf), _T("??"));
    }

    hdcsrc = GetDC(NULL);
    hdc = CreateCompatibleDC(hdcsrc);
    hBitmap = CreateCompatibleBitmap(hdcsrc, 16, 16);
    ReleaseDC(NULL, hdcsrc);

    if (hdc && hBitmap)
    {
        hBmpNew = CreateBitmap(16, 16, 1, 1, NULL);
        if (hBmpNew)
        {
            hBmpOld = SelectObject(hdc, hBitmap);
            rect.right = 16;
            rect.left = 0;
            rect.bottom = 16;
            rect.top = 0;

            SetBkColor(hdc, GetSysColor(COLOR_HIGHLIGHT));
            SetTextColor(hdc, GetSysColor(COLOR_HIGHLIGHTTEXT));

            ExtTextOut(hdc, rect.left, rect.top, ETO_OPAQUE, &rect, _T(""), 0, NULL);

            hFont = CreateFont(-11, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET,
                               OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                               DEFAULT_QUALITY, FF_DONTCARE, _T("Tahoma"));

            hFontOld = SelectObject(hdc, hFont);
            DrawText(hdc, _tcsupr(szBuf), 2, &rect, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
            SelectObject(hdc, hBmpNew);
            PatBlt(hdc, 0, 0, 16, 16, BLACKNESS);
            SelectObject(hdc, hBmpOld);
            SelectObject(hdc, hFontOld);

            IconInfo.hbmColor = hBitmap;
            IconInfo.hbmMask = hBmpNew;
            IconInfo.fIcon = TRUE;

            hIcon = CreateIconIndirect(&IconInfo);

            DeleteObject(hBmpNew);
            DeleteObject(hBmpOld);
            DeleteObject(hFont);
        }
    }

    DeleteDC(hdc);
    DeleteObject(hBitmap);

    return hIcon;
}