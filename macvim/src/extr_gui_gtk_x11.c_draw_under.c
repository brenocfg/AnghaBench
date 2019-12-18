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
struct TYPE_4__ {int /*<<< orphan*/  text_gc; TYPE_1__* drawarea; int /*<<< orphan*/  fgcolor; int /*<<< orphan*/  spcolor; } ;
struct TYPE_3__ {int /*<<< orphan*/  window; } ;

/* Variables and functions */
 int DRAW_UNDERC ; 
 int DRAW_UNDERL ; 
 int FILL_X (int) ; 
 int FILL_Y (int) ; 
 int /*<<< orphan*/  gdk_draw_line (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  gdk_draw_point (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  gdk_gc_set_foreground (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ gui ; 
 int p_linespace ; 

__attribute__((used)) static void
draw_under(int flags, int row, int col, int cells)
{
    int			i;
    int			offset;
    static const int	val[8] = {1, 0, 0, 0, 1, 2, 2, 2 };
    int			y = FILL_Y(row + 1) - 1;

    /* Undercurl: draw curl at the bottom of the character cell. */
    if (flags & DRAW_UNDERC)
    {
	gdk_gc_set_foreground(gui.text_gc, gui.spcolor);
	for (i = FILL_X(col); i < FILL_X(col + cells); ++i)
	{
	    offset = val[i % 8];
	    gdk_draw_point(gui.drawarea->window, gui.text_gc, i, y - offset);
	}
	gdk_gc_set_foreground(gui.text_gc, gui.fgcolor);
    }

    /* Underline: draw a line at the bottom of the character cell. */
    if (flags & DRAW_UNDERL)
    {
	/* When p_linespace is 0, overwrite the bottom row of pixels.
	 * Otherwise put the line just below the character. */
	if (p_linespace > 1)
	    y -= p_linespace - 1;
	gdk_draw_line(gui.drawarea->window, gui.text_gc,
		      FILL_X(col), y,
		      FILL_X(col + cells) - 1, y);
    }
}