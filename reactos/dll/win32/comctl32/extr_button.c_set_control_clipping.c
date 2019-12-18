#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  bottom; int /*<<< orphan*/  right; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
typedef  TYPE_1__ RECT ;
typedef  int /*<<< orphan*/  POINT ;
typedef  scalar_t__ HRGN ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 scalar_t__ CreateRectRgn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPtoLP (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  DeleteObject (scalar_t__) ; 
 int GetClipRgn (int /*<<< orphan*/ ,scalar_t__) ; 
 int GetLayout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IntersectClipRect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int LAYOUT_RTL ; 

HRGN set_control_clipping( HDC hdc, const RECT *rect )
{
    RECT rc = *rect;
    HRGN hrgn = CreateRectRgn( 0, 0, 0, 0 );

    if (GetClipRgn( hdc, hrgn ) != 1)
    {
        DeleteObject( hrgn );
        hrgn = 0;
    }
    DPtoLP( hdc, (POINT *)&rc, 2 );
    if (GetLayout( hdc ) & LAYOUT_RTL)  /* compensate for the shifting done by IntersectClipRect */
    {
        rc.left++;
        rc.right++;
    }
    IntersectClipRect( hdc, rc.left, rc.top, rc.right, rc.bottom );
    return hrgn;
}