#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  HIMAGELIST ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  HBITMAP ;

/* Variables and functions */
 int /*<<< orphan*/  BitBlt (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  COLOR_3DHILIGHT ; 
 int /*<<< orphan*/  COLOR_3DSHADOW ; 
 int /*<<< orphan*/  CreateBitmap (scalar_t__,scalar_t__,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CreateCompatibleBitmap (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  CreateCompatibleDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetSysColorBrush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ILD_MASK ; 
 int /*<<< orphan*/  ImageList_DrawEx (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ImageList_GetIconSize (int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 int NOTSRCERASE ; 
 int /*<<< orphan*/  RGB (int,int,int) ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetBkColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void TOOLBAR_DrawMasked(HIMAGELIST himl, int index, HDC hdc, INT x, INT y, UINT draw_flags)
{
    INT cx, cy;
    HBITMAP hbmMask, hbmImage;
    HDC hdcMask, hdcImage;

    ImageList_GetIconSize(himl, &cx, &cy);

    /* Create src image */
    hdcImage = CreateCompatibleDC(hdc);
    hbmImage = CreateCompatibleBitmap(hdc, cx, cy);
    SelectObject(hdcImage, hbmImage);
    ImageList_DrawEx(himl, index, hdcImage, 0, 0, cx, cy,
                     RGB(0xff, 0xff, 0xff), RGB(0,0,0), draw_flags);

    /* Create Mask */
    hdcMask = CreateCompatibleDC(0);
    hbmMask = CreateBitmap(cx, cy, 1, 1, NULL);
    SelectObject(hdcMask, hbmMask);

    /* Remove the background and all white pixels */
    ImageList_DrawEx(himl, index, hdcMask, 0, 0, cx, cy,
                     RGB(0xff, 0xff, 0xff), RGB(0,0,0), ILD_MASK);
    SetBkColor(hdcImage, RGB(0xff, 0xff, 0xff));
    BitBlt(hdcMask, 0, 0, cx, cy, hdcImage, 0, 0, NOTSRCERASE);

    /* draw the new mask 'etched' to hdc */
    SetBkColor(hdc, RGB(255, 255, 255));
    SelectObject(hdc, GetSysColorBrush(COLOR_3DHILIGHT));
    /* E20746 op code is (Dst ^ (Src & (Pat ^ Dst))) */
    BitBlt(hdc, x + 1, y + 1, cx, cy, hdcMask, 0, 0, 0xE20746);
    SelectObject(hdc, GetSysColorBrush(COLOR_3DSHADOW));
    BitBlt(hdc, x, y, cx, cy, hdcMask, 0, 0, 0xE20746);

    /* Cleanup */
    DeleteObject(hbmImage);
    DeleteDC(hdcImage);
    DeleteObject (hbmMask);
    DeleteDC(hdcMask);
}