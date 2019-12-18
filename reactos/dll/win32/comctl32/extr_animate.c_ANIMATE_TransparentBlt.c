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
struct TYPE_5__ {TYPE_1__* inbih; int /*<<< orphan*/  transparentColor; } ;
struct TYPE_4__ {int /*<<< orphan*/  biHeight; int /*<<< orphan*/  biWidth; } ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  HBITMAP ;
typedef  TYPE_2__ ANIMATE_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  BitBlt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateBitmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CreateCompatibleDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RGB (int,int,int) ; 
 int /*<<< orphan*/  SRCAND ; 
 int /*<<< orphan*/  SRCCOPY ; 
 int /*<<< orphan*/  SRCPAINT ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetBkColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetTextColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ANIMATE_TransparentBlt(ANIMATE_INFO const *infoPtr, HDC hdcDest, HDC hdcSource)
{
    HDC hdcMask;
    HBITMAP hbmMask;
    HBITMAP hbmOld;

    /* create a transparency mask */
    hdcMask = CreateCompatibleDC(hdcDest);
    hbmMask = CreateBitmap(infoPtr->inbih->biWidth, infoPtr->inbih->biHeight, 1,1,NULL);
    hbmOld = SelectObject(hdcMask, hbmMask);

    SetBkColor(hdcSource,infoPtr->transparentColor);
    BitBlt(hdcMask,0,0,infoPtr->inbih->biWidth, infoPtr->inbih->biHeight,hdcSource,0,0,SRCCOPY);

    /* mask the source bitmap */
    SetBkColor(hdcSource, RGB(0,0,0));
    SetTextColor(hdcSource, RGB(255,255,255));
    BitBlt(hdcSource, 0, 0, infoPtr->inbih->biWidth, infoPtr->inbih->biHeight, hdcMask, 0, 0, SRCAND);

    /* mask the destination bitmap */
    SetBkColor(hdcDest, RGB(255,255,255));
    SetTextColor(hdcDest, RGB(0,0,0));
    BitBlt(hdcDest, 0, 0, infoPtr->inbih->biWidth, infoPtr->inbih->biHeight, hdcMask, 0, 0, SRCAND);

    /* combine source and destination */
    BitBlt(hdcDest,0,0,infoPtr->inbih->biWidth, infoPtr->inbih->biHeight,hdcSource,0,0,SRCPAINT);

    SelectObject(hdcMask, hbmOld);
    DeleteObject(hbmMask);
    DeleteDC(hdcMask);
}