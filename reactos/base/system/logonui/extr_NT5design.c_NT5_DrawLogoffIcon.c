#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_5__ {int cx; int cy; int /*<<< orphan*/  hInstance; } ;
struct TYPE_4__ {int /*<<< orphan*/  bmHeight; int /*<<< orphan*/  bmWidth; } ;
typedef  scalar_t__ HDC ;
typedef  scalar_t__ HBITMAP ;
typedef  TYPE_1__ BITMAP ;

/* Variables and functions */
 int /*<<< orphan*/  BitBlt (scalar_t__,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ CreateCompatibleDC (scalar_t__) ; 
 int /*<<< orphan*/  DeleteDC (scalar_t__) ; 
 int /*<<< orphan*/  DeleteObject (scalar_t__) ; 
 int /*<<< orphan*/  GetObjectW (scalar_t__,int,TYPE_1__*) ; 
 int /*<<< orphan*/  IDB_MAIN_ROS_LOGO ; 
 int /*<<< orphan*/  IMAGE_BITMAP ; 
 int /*<<< orphan*/  LR_DEFAULTCOLOR ; 
 scalar_t__ LoadImageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKEINTRESOURCEW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SRCCOPY ; 
 int /*<<< orphan*/  SelectObject (scalar_t__,scalar_t__) ; 
 TYPE_2__* g_pInfo ; 

__attribute__((used)) static VOID
NT5_DrawLogoffIcon(HDC hdcMem)
{
    HBITMAP hBitmap;
    BITMAP bitmap;
    HDC hTempDC;

    /* Load the XP logo */
    hBitmap = (HBITMAP)LoadImageW(g_pInfo->hInstance,
                                  MAKEINTRESOURCEW(IDB_MAIN_ROS_LOGO),
                                  IMAGE_BITMAP,
                                  0,
                                  0,
                                  LR_DEFAULTCOLOR);
    if (hBitmap)
    {
        /* Get the bitmap dimensions */
        GetObjectW(hBitmap, sizeof(BITMAP), &bitmap);

        /* Create a temp DC for the bitmap */
        hTempDC = CreateCompatibleDC(hdcMem);
        if (hTempDC)
        {
            /* Select the bitmap onto the temp DC */
            SelectObject(hTempDC, hBitmap);

            /* Paint it onto the centre block */
            BitBlt(hdcMem,
                   (g_pInfo->cx / 2) + 35,
                   (g_pInfo->cy / 2) - 72,
                   bitmap.bmWidth,
                   bitmap.bmHeight,
                   hTempDC,
                   0,
                   0,
                   SRCCOPY);

            /* Delete the DC */
            DeleteDC(hTempDC);
        }

        /* Delete the bitmap */
        DeleteObject(hBitmap);
    }
}