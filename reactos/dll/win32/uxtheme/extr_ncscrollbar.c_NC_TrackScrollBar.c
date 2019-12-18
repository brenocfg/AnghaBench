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
typedef  int WPARAM ;
typedef  int /*<<< orphan*/  POINT ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int HTHSCROLL ; 
 int HTVSCROLL ; 
 int /*<<< orphan*/  SB_HORZ ; 
 int /*<<< orphan*/  SB_VERT ; 
 int /*<<< orphan*/  SCROLL_TrackScrollBar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SC_HSCROLL ; 

void NC_TrackScrollBar( HWND hwnd, WPARAM wParam, POINT pt )
{
    INT scrollbar;
    
    if ((wParam & 0xfff0) == SC_HSCROLL)
    {
        if ((wParam & 0x0f) != HTHSCROLL) return;
        scrollbar = SB_HORZ;
    }
    else  /* SC_VSCROLL */
    {
        if ((wParam & 0x0f) != HTVSCROLL) return;
        scrollbar = SB_VERT;
    }
    SCROLL_TrackScrollBar( hwnd, scrollbar, pt );
}