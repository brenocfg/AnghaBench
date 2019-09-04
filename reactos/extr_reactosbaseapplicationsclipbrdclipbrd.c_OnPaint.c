#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ps ;
typedef  int /*<<< orphan*/  WPARAM ;
struct TYPE_10__ {int uDisplayFormat; int /*<<< orphan*/  hInstance; int /*<<< orphan*/  hMainWnd; } ;
struct TYPE_9__ {int /*<<< orphan*/  hdc; int /*<<< orphan*/  rcPaint; scalar_t__ fErase; } ;
typedef  int /*<<< orphan*/  RECT ;
typedef  int /*<<< orphan*/  PPAINTSTRUCT ;
typedef  TYPE_1__ PAINTSTRUCT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HGLOBAL ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  HBRUSH ;
typedef  int /*<<< orphan*/  COLORREF ;

/* Variables and functions */
 int /*<<< orphan*/  BeginPaint (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  BitBltFromClipboard (TYPE_1__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  CF_BITMAP 141 
#define  CF_DIB 140 
#define  CF_DIBV5 139 
#define  CF_DSPBITMAP 138 
#define  CF_DSPENHMETAFILE 137 
#define  CF_DSPMETAFILEPICT 136 
#define  CF_DSPTEXT 135 
#define  CF_ENHMETAFILE 134 
#define  CF_METAFILEPICT 133 
#define  CF_NONE 132 
#define  CF_OEMTEXT 131 
#define  CF_OWNERDISPLAY 130 
#define  CF_TEXT 129 
#define  CF_UNICODETEXT 128 
 scalar_t__ COLOR_WINDOW ; 
 scalar_t__ COLOR_WINDOWTEXT ; 
 int /*<<< orphan*/  CloseClipboard () ; 
 int /*<<< orphan*/  CopyMemory (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  DIB_RGB_COLORS ; 
 int DT_CENTER ; 
 int DT_NOPREFIX ; 
 int DT_WORDBREAK ; 
 int /*<<< orphan*/  DrawTextFromClipboard (int,TYPE_1__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DrawTextFromResource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ERROR_UNSUPPORTED_FORMAT ; 
 int /*<<< orphan*/  EndPaint (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  FillRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GMEM_MOVEABLE ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetSysColor (scalar_t__) ; 
 int /*<<< orphan*/  GlobalAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GlobalFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GlobalLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GlobalUnlock (int /*<<< orphan*/ ) ; 
 TYPE_3__ Globals ; 
 int /*<<< orphan*/  OpenClipboard (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PlayEnhMetaFileFromClipboard (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PlayMetaFileFromClipboard (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RealizeClipboardPalette (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SRCCOPY ; 
 int /*<<< orphan*/  Scrollstate ; 
 int /*<<< orphan*/  SendClipboardOwnerMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetBkColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetDIBitsToDeviceFromClipboard (int,TYPE_1__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetTextColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WM_PAINTCLIPBOARD ; 

__attribute__((used)) static void OnPaint(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    COLORREF crOldBkColor, crOldTextColor;
    RECT rc;

    if (!OpenClipboard(Globals.hMainWnd))
        return;

    hdc = BeginPaint(hWnd, &ps);

    /* Erase the background if needed */
    if (ps.fErase)
        FillRect(ps.hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

    /* Set the correct background and text colors */
    crOldBkColor   = SetBkColor(ps.hdc, GetSysColor(COLOR_WINDOW));
    crOldTextColor = SetTextColor(ps.hdc, GetSysColor(COLOR_WINDOWTEXT));

    /* Realize the clipboard palette if there is one */
    RealizeClipboardPalette(ps.hdc);

    switch (Globals.uDisplayFormat)
    {
        case CF_NONE:
        {
            /* The clipboard is empty */
            break;
        }

        case CF_DSPTEXT:
        case CF_TEXT:
        case CF_OEMTEXT:
        case CF_UNICODETEXT:
        {
            DrawTextFromClipboard(Globals.uDisplayFormat, ps, Scrollstate);
            break;
        }

        case CF_DSPBITMAP:
        case CF_BITMAP:
        {
            BitBltFromClipboard(ps, Scrollstate, SRCCOPY);
            break;
        }

        case CF_DIB:
        case CF_DIBV5:
        {
            SetDIBitsToDeviceFromClipboard(Globals.uDisplayFormat, ps, Scrollstate, DIB_RGB_COLORS);
            break;
        }

        case CF_DSPMETAFILEPICT:
        case CF_METAFILEPICT:
        {
            GetClientRect(hWnd, &rc);
            PlayMetaFileFromClipboard(hdc, &rc);
            break;
        }

        case CF_DSPENHMETAFILE:
        case CF_ENHMETAFILE:
        {
            GetClientRect(hWnd, &rc);
            PlayEnhMetaFileFromClipboard(hdc, &rc);
            break;
        }

        // case CF_PALETTE:
            // TODO: Draw a palette with squares filled with colors.
            // break;

        case CF_OWNERDISPLAY:
        {
            HGLOBAL hglb;
            PPAINTSTRUCT pps;

            hglb = GlobalAlloc(GMEM_MOVEABLE, sizeof(ps));
            if (hglb)
            {
                pps = GlobalLock(hglb);
                CopyMemory(pps, &ps, sizeof(ps));
                GlobalUnlock(hglb);

                SendClipboardOwnerMessage(TRUE, WM_PAINTCLIPBOARD,
                                          (WPARAM)hWnd, (LPARAM)hglb);

                GlobalFree(hglb);
            }
            break;
        }

        default:
        {
            GetClientRect(hWnd, &rc);
            DrawTextFromResource(Globals.hInstance, ERROR_UNSUPPORTED_FORMAT,
                                 hdc, &rc, DT_CENTER | DT_WORDBREAK | DT_NOPREFIX);
            break;
        }
    }

    /* Restore the original colors */
    SetTextColor(ps.hdc, crOldTextColor);
    SetBkColor(ps.hdc, crOldBkColor);

    EndPaint(hWnd, &ps);

    CloseClipboard();
}