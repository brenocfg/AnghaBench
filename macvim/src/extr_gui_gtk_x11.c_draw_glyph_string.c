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
struct TYPE_4__ {int char_width; int /*<<< orphan*/  text_gc; TYPE_1__* drawarea; int /*<<< orphan*/  font_can_bold; int /*<<< orphan*/  fgcolor; int /*<<< orphan*/  char_height; int /*<<< orphan*/  bgcolor; } ;
struct TYPE_3__ {int /*<<< orphan*/  window; } ;
typedef  int /*<<< orphan*/  PangoGlyphString ;
typedef  int /*<<< orphan*/  PangoFont ;

/* Variables and functions */
 int DRAW_BOLD ; 
 int DRAW_TRANSP ; 
 int /*<<< orphan*/  FILL_X (int) ; 
 int /*<<< orphan*/  FILL_Y (int) ; 
 scalar_t__ TEXT_X (int) ; 
 int /*<<< orphan*/  TEXT_Y (int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  gdk_draw_glyphs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gdk_draw_rectangle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdk_gc_set_foreground (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ gui ; 

__attribute__((used)) static void
draw_glyph_string(int row, int col, int num_cells, int flags,
		  PangoFont *font, PangoGlyphString *glyphs)
{
    if (!(flags & DRAW_TRANSP))
    {
	gdk_gc_set_foreground(gui.text_gc, gui.bgcolor);

	gdk_draw_rectangle(gui.drawarea->window,
			   gui.text_gc,
			   TRUE,
			   FILL_X(col),
			   FILL_Y(row),
			   num_cells * gui.char_width,
			   gui.char_height);
    }

    gdk_gc_set_foreground(gui.text_gc, gui.fgcolor);

    gdk_draw_glyphs(gui.drawarea->window,
		    gui.text_gc,
		    font,
		    TEXT_X(col),
		    TEXT_Y(row),
		    glyphs);

    /* redraw the contents with an offset of 1 to emulate bold */
    if ((flags & DRAW_BOLD) && !gui.font_can_bold)
	gdk_draw_glyphs(gui.drawarea->window,
			gui.text_gc,
			font,
			TEXT_X(col) + 1,
			TEXT_Y(row),
			glyphs);
}