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
struct TYPE_5__ {scalar_t__ char_height; scalar_t__ char_width; int /*<<< orphan*/  col; int /*<<< orphan*/  row; } ;
struct TYPE_4__ {scalar_t__ top; scalar_t__ bottom; scalar_t__ right; scalar_t__ left; } ;
typedef  TYPE_1__ Rect ;

/* Variables and functions */
 scalar_t__ FILL_X (int /*<<< orphan*/ ) ; 
 scalar_t__ FILL_Y (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FrameRect (TYPE_1__*) ; 
 TYPE_2__ gui ; 
 int /*<<< orphan*/  gui_mch_set_fg_color (int /*<<< orphan*/ ) ; 
 scalar_t__ mb_lefthalve (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
gui_mch_draw_hollow_cursor(guicolor_T color)
{
    Rect rc;

    /*
     * Note: FrameRect() excludes right and bottom of rectangle.
     */
    rc.left = FILL_X(gui.col);
    rc.top = FILL_Y(gui.row);
    rc.right = rc.left + gui.char_width;
#ifdef FEAT_MBYTE
    if (mb_lefthalve(gui.row, gui.col))
	rc.right += gui.char_width;
#endif
    rc.bottom = rc.top + gui.char_height;

    gui_mch_set_fg_color(color);

    FrameRect(&rc);
}