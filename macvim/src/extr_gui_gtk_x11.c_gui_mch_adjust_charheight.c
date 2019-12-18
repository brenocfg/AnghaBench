#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int char_height; int char_ascent; int /*<<< orphan*/  text_context; int /*<<< orphan*/  norm_font; } ;
typedef  int /*<<< orphan*/  PangoFontMetrics ;

/* Variables and functions */
 void* MAX (int,int) ; 
 int OK ; 
 int PANGO_PIXELS (int) ; 
 int PANGO_SCALE ; 
 TYPE_1__ gui ; 
 int p_linespace ; 
 int /*<<< orphan*/  pango_context_get_language (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pango_context_get_metrics (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pango_font_metrics_get_ascent (int /*<<< orphan*/ *) ; 
 int pango_font_metrics_get_descent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pango_font_metrics_unref (int /*<<< orphan*/ *) ; 

int
gui_mch_adjust_charheight(void)
{
    PangoFontMetrics	*metrics;
    int			ascent;
    int			descent;

    metrics = pango_context_get_metrics(gui.text_context, gui.norm_font,
				pango_context_get_language(gui.text_context));
    ascent  = pango_font_metrics_get_ascent(metrics);
    descent = pango_font_metrics_get_descent(metrics);

    pango_font_metrics_unref(metrics);

    gui.char_height = (ascent + descent + PANGO_SCALE - 1) / PANGO_SCALE
								+ p_linespace;
    /* LINTED: avoid warning: bitwise operation on signed value */
    gui.char_ascent = PANGO_PIXELS(ascent + p_linespace * PANGO_SCALE / 2);

    /* A not-positive value of char_height may crash Vim.  Only happens
     * if 'linespace' is negative (which does make sense sometimes). */
    gui.char_ascent = MAX(gui.char_ascent, 0);
    gui.char_height = MAX(gui.char_height, gui.char_ascent + 1);

    return OK;
}