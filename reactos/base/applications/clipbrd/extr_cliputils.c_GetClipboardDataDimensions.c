#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bmp ;
typedef  int UINT ;
struct TYPE_11__ {int /*<<< orphan*/  hMainWnd; } ;
struct TYPE_10__ {int /*<<< orphan*/  bmHeight; int /*<<< orphan*/  bmWidth; } ;
struct TYPE_9__ {int /*<<< orphan*/  bcHeight; int /*<<< orphan*/  bcWidth; } ;
struct TYPE_8__ {int biSize; int /*<<< orphan*/  biHeight; int /*<<< orphan*/  biWidth; } ;
struct TYPE_7__ {int /*<<< orphan*/  cy; int /*<<< orphan*/  cx; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  SIZE_T ;
typedef  TYPE_1__ SIZE ;
typedef  void* PVOID ;
typedef  int /*<<< orphan*/  PRECT ;
typedef  int /*<<< orphan*/ * LPCWSTR ;
typedef  int /*<<< orphan*/ * LPCSTR ;
typedef  TYPE_2__* LPBITMAPINFOHEADER ;
typedef  TYPE_3__* LPBITMAPCOREHEADER ;
typedef  int /*<<< orphan*/  HGLOBAL ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  HBITMAP ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  int /*<<< orphan*/  BITMAPV5HEADER ;
typedef  int /*<<< orphan*/  BITMAPV4HEADER ;
typedef  int /*<<< orphan*/  BITMAPINFOHEADER ;
typedef  int /*<<< orphan*/  BITMAPCOREHEADER ;
typedef  TYPE_4__ BITMAP ;

/* Variables and functions */
 int /*<<< orphan*/  ANSI_NULL ; 
#define  CF_BITMAP 135 
#define  CF_DIB 134 
#define  CF_DIBV5 133 
#define  CF_DSPBITMAP 132 
#define  CF_DSPTEXT 131 
#define  CF_OEMTEXT 130 
#define  CF_TEXT 129 
#define  CF_UNICODETEXT 128 
 int /*<<< orphan*/  CloseClipboard () ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetClipboardData (int const) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetLineExtentA (void*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GetLineExtentW (void*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GetObjectW (int /*<<< orphan*/ ,int,TYPE_4__*) ; 
 int /*<<< orphan*/  GetTabbedTextExtentA (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetTabbedTextExtentW (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* GlobalLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GlobalUnlock (int /*<<< orphan*/ ) ; 
 TYPE_5__ Globals ; 
 int /*<<< orphan*/  HIWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OpenClipboard (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetRect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetRectEmpty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UNICODE_NULL ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

BOOL GetClipboardDataDimensions(UINT uFormat, PRECT pRc)
{
    SetRectEmpty(pRc);

    if (!OpenClipboard(Globals.hMainWnd))
    {
        return FALSE;
    }

    switch (uFormat)
    {
        case CF_DSPBITMAP:
        case CF_BITMAP:
        {
            HBITMAP hBitmap;
            BITMAP bmp;

            hBitmap = (HBITMAP)GetClipboardData(CF_BITMAP);
            GetObjectW(hBitmap, sizeof(bmp), &bmp);
            SetRect(pRc, 0, 0, bmp.bmWidth, bmp.bmHeight);
            break;
        }

        case CF_DIB:
        case CF_DIBV5:
        {
            HGLOBAL hGlobal;
            LPBITMAPINFOHEADER lpInfoHeader;

            hGlobal = GetClipboardData(uFormat);
            if (!hGlobal)
                break;

            lpInfoHeader = GlobalLock(hGlobal);
            if (!lpInfoHeader)
                break;

            if (lpInfoHeader->biSize == sizeof(BITMAPCOREHEADER))
            {
                LPBITMAPCOREHEADER lpCoreHeader = (LPBITMAPCOREHEADER)lpInfoHeader;
                SetRect(pRc, 0, 0,
                        lpCoreHeader->bcWidth,
                        lpCoreHeader->bcHeight);
            }
            else if ((lpInfoHeader->biSize == sizeof(BITMAPINFOHEADER)) ||
                     (lpInfoHeader->biSize == sizeof(BITMAPV4HEADER))   ||
                     (lpInfoHeader->biSize == sizeof(BITMAPV5HEADER)))
            {
                SetRect(pRc, 0, 0,
                        lpInfoHeader->biWidth,
                        /* NOTE: biHeight < 0 for bottom-up DIBs, or > 0 for top-down DIBs */
                        (lpInfoHeader->biHeight > 0) ?  lpInfoHeader->biHeight
                                                     : -lpInfoHeader->biHeight);
            }
            else
            {
                /* Invalid format */
            }

            GlobalUnlock(hGlobal);
            break;
        }

        case CF_DSPTEXT:
        case CF_TEXT:
        case CF_OEMTEXT:
        case CF_UNICODETEXT:
        {
            HDC hDC;
            HGLOBAL hGlobal;
            PVOID lpText, ptr;
            DWORD dwSize;
            SIZE txtSize = {0, 0};
            SIZE_T lineSize;

            hGlobal = GetClipboardData(uFormat);
            if (!hGlobal)
                break;

            lpText = GlobalLock(hGlobal);
            if (!lpText)
                break;

            hDC = GetDC(Globals.hMainWnd);

            /* Find the size of the rectangle enclosing the text */
            for (;;)
            {
                if (uFormat == CF_UNICODETEXT)
                {
                    if (*(LPCWSTR)lpText == UNICODE_NULL)
                        break;
                    lineSize = GetLineExtentW(lpText, (LPCWSTR*)&ptr);
                    dwSize = GetTabbedTextExtentW(hDC, lpText, lineSize, 0, NULL);
                }
                else
                {
                    if (*(LPCSTR)lpText == ANSI_NULL)
                        break;
                    lineSize = GetLineExtentA(lpText, (LPCSTR*)&ptr);
                    dwSize = GetTabbedTextExtentA(hDC, lpText, lineSize, 0, NULL);
                }
                txtSize.cx = max(txtSize.cx, LOWORD(dwSize));
                txtSize.cy += HIWORD(dwSize);
                lpText = ptr;
            }

            ReleaseDC(Globals.hMainWnd, hDC);

            GlobalUnlock(hGlobal);

            SetRect(pRc, 0, 0, txtSize.cx, txtSize.cy);
            break;
        }

        default:
        {
            break;
        }
    }

    CloseClipboard();

    return TRUE;
}