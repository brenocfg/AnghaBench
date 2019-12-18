#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  maskBitmap ;
typedef  int /*<<< orphan*/  logoBitmap ;
typedef  int /*<<< orphan*/  bmpi ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_11__ {int bmHeight; int bmWidth; int /*<<< orphan*/  bmPlanes; int /*<<< orphan*/  bmBitsPixel; } ;
struct TYPE_9__ {int biSize; int biWidth; int biHeight; int biPlanes; int biBitCount; int biSizeImage; int /*<<< orphan*/  biCompression; } ;
struct TYPE_10__ {int cxSource; int cySource; int /*<<< orphan*/  iPlanes; int /*<<< orphan*/  iBits; int /*<<< orphan*/ * hBitmap; TYPE_1__ bmiHeader; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  TYPE_2__* PIMGINFO ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/ * HBITMAP ;
typedef  int DWORD ;
typedef  int COLORREF ;
typedef  TYPE_2__ BITMAPINFO ;
typedef  TYPE_4__ BITMAP ;

/* Variables and functions */
 int /*<<< orphan*/  BI_RGB ; 
 int /*<<< orphan*/  CreateCompatibleDC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateDIBSection (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIB_RGB_COLORS ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ *) ; 
 int GetBValue (int) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int GetGValue (int) ; 
 int /*<<< orphan*/  GetObject (int /*<<< orphan*/ *,int,TYPE_4__*) ; 
 int GetPixel (int /*<<< orphan*/ ,int,int) ; 
 int GetRValue (int) ; 
 int /*<<< orphan*/  IDB_ROSLOGO ; 
 int /*<<< orphan*/  IDB_ROSMASK ; 
 int /*<<< orphan*/  IMAGE_BITMAP ; 
 int /*<<< orphan*/  LR_DEFAULTCOLOR ; 
 scalar_t__ LoadImageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKEINTRESOURCEW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_2__*,int) ; 
 int /*<<< orphan*/  hInstance ; 

__attribute__((used)) static VOID
InitLogo(PIMGINFO pImgInfo, HWND hwndDlg)
{
    BITMAP logoBitmap;
    BITMAP maskBitmap;
    BITMAPINFO bmpi;
    HDC hDC = GetDC(hwndDlg);
    HDC hDCLogo = CreateCompatibleDC(NULL);
    HDC hDCMask = CreateCompatibleDC(NULL);
    HBITMAP hMask, hLogo, hAlphaLogo = NULL;
    COLORREF *pBits;
    INT line, column;

    ZeroMemory(pImgInfo, sizeof(*pImgInfo));
    ZeroMemory(&bmpi, sizeof(bmpi));

    hLogo = (HBITMAP)LoadImageW(hInstance, MAKEINTRESOURCEW(IDB_ROSLOGO), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);
    hMask = (HBITMAP)LoadImageW(hInstance, MAKEINTRESOURCEW(IDB_ROSMASK), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);

    if (hLogo != NULL && hMask != NULL)
    {
        GetObject(hLogo, sizeof(logoBitmap), &logoBitmap);
        GetObject(hMask, sizeof(maskBitmap), &maskBitmap);

        if (logoBitmap.bmHeight != maskBitmap.bmHeight || logoBitmap.bmWidth != maskBitmap.bmWidth)
            goto Cleanup;

        bmpi.bmiHeader.biSize = sizeof(BITMAPINFO);
        bmpi.bmiHeader.biWidth = logoBitmap.bmWidth;
        bmpi.bmiHeader.biHeight = logoBitmap.bmHeight;
        bmpi.bmiHeader.biPlanes = 1;
        bmpi.bmiHeader.biBitCount = 32;
        bmpi.bmiHeader.biCompression = BI_RGB;
        bmpi.bmiHeader.biSizeImage = 4 * logoBitmap.bmWidth * logoBitmap.bmHeight;

        /* Create a premultiplied bitmap */
        hAlphaLogo = CreateDIBSection(hDC, &bmpi, DIB_RGB_COLORS, (PVOID*)&pBits, 0, 0);
        if (!hAlphaLogo)
            goto Cleanup;

        SelectObject(hDCLogo, hLogo);
        SelectObject(hDCMask, hMask);

        for (line = logoBitmap.bmHeight - 1; line >= 0; line--)
        {
            for (column = 0; column < logoBitmap.bmWidth; column++)
            {
                COLORREF alpha = GetPixel(hDCMask, column, line) & 0xFF;
                COLORREF Color = GetPixel(hDCLogo, column, line);
                DWORD r, g, b;

                r = GetRValue(Color) * alpha / 255;
                g = GetGValue(Color) * alpha / 255;
                b = GetBValue(Color) * alpha / 255;

                *pBits++ = b | g << 8 | r << 16 | alpha << 24;
            }
        }

        pImgInfo->hBitmap = hAlphaLogo;
        pImgInfo->cxSource = logoBitmap.bmWidth;
        pImgInfo->cySource = logoBitmap.bmHeight;
        pImgInfo->iBits = logoBitmap.bmBitsPixel;
        pImgInfo->iPlanes = logoBitmap.bmPlanes;
    }

Cleanup:
    DeleteObject(hMask);
    DeleteObject(hLogo);
    DeleteDC(hDCMask);
    DeleteDC(hDCLogo);
}