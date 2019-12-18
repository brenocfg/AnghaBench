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
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_11__ {int bcBitCount; int /*<<< orphan*/  bcHeight; int /*<<< orphan*/  bcWidth; } ;
struct TYPE_10__ {int biSize; int biClrUsed; int biBitCount; scalar_t__ biCompression; int /*<<< orphan*/  biHeight; int /*<<< orphan*/  biWidth; } ;
struct TYPE_9__ {int /*<<< orphan*/  hdc; } ;
struct TYPE_8__ {int /*<<< orphan*/  CurrentY; int /*<<< orphan*/  CurrentX; } ;
typedef  TYPE_1__ SCROLLSTATE ;
typedef  int /*<<< orphan*/  RGBTRIPLE ;
typedef  int /*<<< orphan*/  RGBQUAD ;
typedef  TYPE_2__ PAINTSTRUCT ;
typedef  scalar_t__ LPBYTE ;
typedef  TYPE_3__* LPBITMAPINFOHEADER ;
typedef  int /*<<< orphan*/  LPBITMAPINFO ;
typedef  TYPE_4__* LPBITMAPCOREHEADER ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  HGLOBAL ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BITMAPV5HEADER ;
typedef  int /*<<< orphan*/  BITMAPV4HEADER ;
typedef  int /*<<< orphan*/  BITMAPINFOHEADER ;
typedef  int /*<<< orphan*/  BITMAPCOREHEADER ;

/* Variables and functions */
 scalar_t__ BI_BITFIELDS ; 
 int /*<<< orphan*/  DIB_RGB_COLORS ; 
 int /*<<< orphan*/  GetClipboardData (int /*<<< orphan*/ ) ; 
 TYPE_3__* GlobalLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GlobalUnlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetDIBitsToDevice (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void SetDIBitsToDeviceFromClipboard(UINT uFormat, PAINTSTRUCT ps, SCROLLSTATE state, UINT fuColorUse)
{
    HGLOBAL hGlobal;
    LPBITMAPINFOHEADER lpInfoHeader;
    LPBYTE lpBits;
    LONG bmWidth, bmHeight;
    DWORD dwPalSize = 0;

    hGlobal = GetClipboardData(uFormat);
    if (!hGlobal)
        return;

    lpInfoHeader = GlobalLock(hGlobal);
    if (!lpInfoHeader)
        return;

    if (lpInfoHeader->biSize == sizeof(BITMAPCOREHEADER))
    {
        LPBITMAPCOREHEADER lpCoreHeader = (LPBITMAPCOREHEADER)lpInfoHeader;

        dwPalSize = 0;

        if (lpCoreHeader->bcBitCount <= 8)
        {
            dwPalSize = (1 << lpCoreHeader->bcBitCount);

            if (fuColorUse == DIB_RGB_COLORS)
                dwPalSize *= sizeof(RGBTRIPLE);
            else
                dwPalSize *= sizeof(WORD);
        }

        bmWidth  = lpCoreHeader->bcWidth;
        bmHeight = lpCoreHeader->bcHeight;
    }
    else if ((lpInfoHeader->biSize == sizeof(BITMAPINFOHEADER)) ||
             (lpInfoHeader->biSize == sizeof(BITMAPV4HEADER))   ||
             (lpInfoHeader->biSize == sizeof(BITMAPV5HEADER)))
    {
        dwPalSize = lpInfoHeader->biClrUsed;

        if ((dwPalSize == 0) && (lpInfoHeader->biBitCount <= 8))
            dwPalSize = (1 << lpInfoHeader->biBitCount);

        if (fuColorUse == DIB_RGB_COLORS)
            dwPalSize *= sizeof(RGBQUAD);
        else
            dwPalSize *= sizeof(WORD);

        if (/*(lpInfoHeader->biSize == sizeof(BITMAPINFOHEADER)) &&*/
            (lpInfoHeader->biCompression == BI_BITFIELDS))
        {
            dwPalSize += 3 * sizeof(DWORD);
        }

        /*
         * This is a (disabled) hack for Windows, when uFormat == CF_DIB
         * it needs yet another extra 3 DWORDs, in addition to the
         * ones already taken into account in via the compression.
         * This problem doesn't happen when uFormat == CF_DIBV5
         * (in that case, when compression is taken into account,
         * everything is nice).
         *
         * NOTE 1: This fix is only for us, because when one pastes DIBs
         * directly in apps, the bitmap offset problem is still present.
         *
         * NOTE 2: The problem can be seen with Windows' clipbrd.exe if
         * one copies a CF_DIB image in the clipboard. By default Windows'
         * clipbrd.exe works with CF_DIBV5 and CF_BITMAP, so the problem
         * is unseen, and the clipboard doesn't have to convert to CF_DIB.
         *
         * FIXME: investigate!!
         * ANSWER: this is a Windows bug; part of the answer is there:
         * https://social.msdn.microsoft.com/Forums/windowsdesktop/en-US/ac7ab3b5-8609-4478-b86a-976dab44c271/bug-clipboard-format-conversions-cfdib-cfdibv5-cfdib
         * May be related:
         * https://blog.talosintelligence.com/2015/10/dangerous-clipboard.html
         */
#if 0
        if ((lpInfoHeader->biSize == sizeof(BITMAPINFOHEADER)) &&
            (lpInfoHeader->biCompression == BI_BITFIELDS))
        {
            dwPalSize += 3 * sizeof(DWORD);
        }
#endif

        bmWidth  = lpInfoHeader->biWidth;
        /* NOTE: biHeight < 0 for bottom-up DIBs, or > 0 for top-down DIBs */
        bmHeight = lpInfoHeader->biHeight;
    }
    else
    {
        /* Invalid format */
        GlobalUnlock(hGlobal);
        return;
    }

    lpBits = (LPBYTE)lpInfoHeader + lpInfoHeader->biSize + dwPalSize;

    /*
     * The seventh parameter (YSrc) of SetDIBitsToDevice always designates
     * the Y-coordinate of the "lower-left corner" of the image, be the DIB
     * in bottom-up or top-down mode.
     */
    SetDIBitsToDevice(ps.hdc,
                      -state.CurrentX, // ps.rcPaint.left,
                      -state.CurrentY, // ps.rcPaint.top,
                      bmWidth,
                      bmHeight,
                      0, // ps.rcPaint.left + state.CurrentX,
                      0, // -(ps.rcPaint.top  + state.CurrentY),
                      0, // uStartScan,
                      bmHeight,
                      lpBits,
                      (LPBITMAPINFO)lpInfoHeader,
                      fuColorUse);

    GlobalUnlock(hGlobal);
}