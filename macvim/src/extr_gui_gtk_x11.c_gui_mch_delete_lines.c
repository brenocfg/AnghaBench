#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ visibility; int scroll_region_left; int char_width; int scroll_region_right; int char_height; int scroll_region_bot; TYPE_1__* drawarea; int /*<<< orphan*/  text_gc; int /*<<< orphan*/  bgcolor; int /*<<< orphan*/  fgcolor; } ;
struct TYPE_3__ {int /*<<< orphan*/  window; } ;

/* Variables and functions */
 int /*<<< orphan*/  FILL_X (int) ; 
 int /*<<< orphan*/  FILL_Y (int) ; 
 scalar_t__ GDK_VISIBILITY_FULLY_OBSCURED ; 
 int /*<<< orphan*/  check_copy_area () ; 
 int /*<<< orphan*/  gdk_gc_set_background (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdk_gc_set_foreground (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdk_window_copy_area (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 TYPE_2__ gui ; 
 int /*<<< orphan*/  gui_clear_block (int,int,int,int) ; 

void
gui_mch_delete_lines(int row, int num_lines)
{
    if (gui.visibility == GDK_VISIBILITY_FULLY_OBSCURED)
	return;			/* Can't see the window */

    gdk_gc_set_foreground(gui.text_gc, gui.fgcolor);
    gdk_gc_set_background(gui.text_gc, gui.bgcolor);

    /* copy one extra pixel, for when bold has spilled over */
    gdk_window_copy_area(gui.drawarea->window, gui.text_gc,
	    FILL_X(gui.scroll_region_left), FILL_Y(row),
	    gui.drawarea->window,
	    FILL_X(gui.scroll_region_left),
	    FILL_Y(row + num_lines),
	    gui.char_width * (gui.scroll_region_right
					    - gui.scroll_region_left + 1) + 1,
	    gui.char_height * (gui.scroll_region_bot - row - num_lines + 1));

    gui_clear_block(gui.scroll_region_bot - num_lines + 1,
						       gui.scroll_region_left,
		    gui.scroll_region_bot, gui.scroll_region_right);
    check_copy_area();
}