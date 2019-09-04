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
typedef  int ULONG ;
struct TYPE_6__ {int /*<<< orphan*/ * hbmColor; int /*<<< orphan*/ * hbmMask; int /*<<< orphan*/  fIcon; } ;
struct TYPE_5__ {int left; int top; int right; int bottom; } ;
typedef  TYPE_1__ RECT ;
typedef  TYPE_2__ ICONINFO ;
typedef  int /*<<< orphan*/ * HICON ;
typedef  int /*<<< orphan*/ * HDC ;
typedef  int /*<<< orphan*/ * HBRUSH ;
typedef  int /*<<< orphan*/ * HBITMAP ;

/* Variables and functions */
 int /*<<< orphan*/ * CreateCompatibleDC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateIconIndirect (TYPE_2__*) ; 
 int /*<<< orphan*/ * CreateSolidBrush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FillRect (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetDC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDB_TRAYICON ; 
 int /*<<< orphan*/  IDB_TRAYMASK ; 
 int /*<<< orphan*/ * LoadBitmapW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKEINTRESOURCEW (int /*<<< orphan*/ ) ; 
 int PerfDataGetProcessorUsage () ; 
 int /*<<< orphan*/  RGB (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SelectObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  hInst ; 

HICON TrayIcon_GetProcessorUsageIcon(void)
{
    HICON     hTrayIcon = NULL;
    HDC       hScreenDC = NULL;
    HDC       hDC = NULL;
    HBITMAP   hBitmap = NULL;
    HBITMAP   hOldBitmap = NULL;
    HBITMAP   hBitmapMask = NULL;
    ICONINFO  iconInfo;
    ULONG     ProcessorUsage;
    int       nLinesToDraw;
    HBRUSH    hBitmapBrush = NULL;
    RECT      rc;

    /*
     * Get a handle to the screen DC
     */
    hScreenDC = GetDC(NULL);
    if (!hScreenDC)
        goto done;

    /*
     * Create our own DC from it
     */
    hDC = CreateCompatibleDC(hScreenDC);
    if (!hDC)
        goto done;

    /*
     * Load the bitmaps
     */
    hBitmap = LoadBitmapW(hInst, MAKEINTRESOURCEW(IDB_TRAYICON));
    hBitmapMask = LoadBitmapW(hInst, MAKEINTRESOURCEW(IDB_TRAYMASK));
    if (!hBitmap || !hBitmapMask)
        goto done;

    hBitmapBrush = CreateSolidBrush(RGB(0, 255, 0));
    if (!hBitmapBrush)
        goto done;

    /*
     * Select the bitmap into our device context
     * so we can draw on it.
     */
    hOldBitmap = (HBITMAP) SelectObject(hDC, hBitmap);

    /*
     * Get the cpu usage
     */
    ProcessorUsage = PerfDataGetProcessorUsage();

    /*
     * Calculate how many lines to draw
     * since we have 11 rows of space
     * to draw the cpu usage instead of
     * just having 10.
     */
    nLinesToDraw = (ProcessorUsage + (ProcessorUsage / 10)) / 11;
    rc.left = 3;
    rc.top = 12 - nLinesToDraw;
    rc.right = 13;
    rc.bottom = 13;

    /*
     * Now draw the cpu usage
     */
    if (nLinesToDraw)
        FillRect(hDC, &rc, hBitmapBrush);

    /*
     * Now that we are done drawing put the
     * old bitmap back.
     */
    hBitmap = SelectObject(hDC, hOldBitmap);
    hOldBitmap = NULL;

    iconInfo.fIcon = TRUE;
    iconInfo.hbmMask = hBitmapMask;
    iconInfo.hbmColor = hBitmap;

    hTrayIcon = CreateIconIndirect(&iconInfo);

done:
    /*
     * Cleanup
     */
    if (hScreenDC)
        ReleaseDC(NULL, hScreenDC);
    if (hDC)
        DeleteDC(hDC);
    if (hBitmapBrush)
        DeleteObject(hBitmapBrush);
    if (hBitmap)
        DeleteObject(hBitmap);
    if (hBitmapMask)
        DeleteObject(hBitmapMask);

    /*
     * Return the newly created tray icon (if successful)
     */
    return hTrayIcon;
}