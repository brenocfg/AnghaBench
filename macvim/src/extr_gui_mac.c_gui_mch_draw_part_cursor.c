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
typedef  int /*<<< orphan*/  guicolor_T ;
struct TYPE_5__ {scalar_t__ char_height; int /*<<< orphan*/  row; scalar_t__ col; } ;
struct TYPE_4__ {scalar_t__ top; scalar_t__ bottom; void* left; void* right; } ;
typedef  TYPE_1__ Rect ;

/* Variables and functions */
 scalar_t__ CURSOR_BAR_RIGHT ; 
 void* FILL_X (scalar_t__) ; 
 scalar_t__ FILL_Y (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FrameRect (TYPE_1__*) ; 
 TYPE_2__ gui ; 
 int /*<<< orphan*/  gui_mch_set_fg_color (int /*<<< orphan*/ ) ; 

void
gui_mch_draw_part_cursor(int w, int h, guicolor_T color)
{
    Rect rc;

#ifdef FEAT_RIGHTLEFT
    /* vertical line should be on the right of current point */
    if (CURSOR_BAR_RIGHT)
	rc.left = FILL_X(gui.col + 1) - w;
    else
#endif
	rc.left = FILL_X(gui.col);
    rc.top = FILL_Y(gui.row) + gui.char_height - h;
    rc.right = rc.left + w;
    rc.bottom = rc.top + h;

    gui_mch_set_fg_color(color);

    FrameRect(&rc);
//    PaintRect(&rc);
}