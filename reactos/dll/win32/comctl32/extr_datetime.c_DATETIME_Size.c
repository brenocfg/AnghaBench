#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ left; void* bottom; void* top; void* right; } ;
struct TYPE_7__ {scalar_t__ right; scalar_t__ left; void* bottom; void* top; } ;
struct TYPE_6__ {void* right; void* left; void* bottom; void* top; } ;
struct TYPE_9__ {int dwStyle; int /*<<< orphan*/  hwndSelf; TYPE_3__ rcDraw; TYPE_2__ checkbox; TYPE_1__ calbutton; TYPE_3__ rcClient; int /*<<< orphan*/  hUpdown; } ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  void* INT ;
typedef  TYPE_4__ DATETIME_INFO ;

/* Variables and functions */
 int DTS_UPDOWN ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int SWP_NOACTIVATE ; 
 int SWP_NOZORDER ; 
 int /*<<< orphan*/  SetWindowPos (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int,void*,int) ; 
 int /*<<< orphan*/  TRACE (char*,void*,void*) ; 

__attribute__((used)) static LRESULT
DATETIME_Size (DATETIME_INFO *infoPtr, INT width, INT height)
{
    /* set size */
    infoPtr->rcClient.bottom = height;
    infoPtr->rcClient.right = width;

    TRACE("Height=%d, Width=%d\n", infoPtr->rcClient.bottom, infoPtr->rcClient.right);

    infoPtr->rcDraw = infoPtr->rcClient;
    
    if (infoPtr->dwStyle & DTS_UPDOWN) {
        SetWindowPos(infoPtr->hUpdown, NULL,
            infoPtr->rcClient.right-14, 0,
            15, infoPtr->rcClient.bottom - infoPtr->rcClient.top,
            SWP_NOACTIVATE | SWP_NOZORDER);
    }
    else {
        /* set the size of the button that drops the calendar down */
        /* FIXME: account for style that allows button on left side */
        infoPtr->calbutton.top   = infoPtr->rcDraw.top;
        infoPtr->calbutton.bottom= infoPtr->rcDraw.bottom;
        infoPtr->calbutton.left  = infoPtr->rcDraw.right-15;
        infoPtr->calbutton.right = infoPtr->rcDraw.right;
    }

    /* set enable/disable button size for show none style being enabled */
    /* FIXME: these dimensions are completely incorrect */
    infoPtr->checkbox.top = infoPtr->rcDraw.top;
    infoPtr->checkbox.bottom = infoPtr->rcDraw.bottom;
    infoPtr->checkbox.left = infoPtr->rcDraw.left;
    infoPtr->checkbox.right = infoPtr->rcDraw.left + 10;

    InvalidateRect(infoPtr->hwndSelf, NULL, FALSE);

    return 0;
}