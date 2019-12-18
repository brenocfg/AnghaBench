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
typedef  int long_u ;
struct TYPE_4__ {int foreground; int background; int /*<<< orphan*/  function; } ;
typedef  TYPE_1__ XGCValues ;
struct TYPE_5__ {int norm_pixel; int back_pixel; int /*<<< orphan*/ * invert_gc; int /*<<< orphan*/  dpy; int /*<<< orphan*/ * back_gc; int /*<<< orphan*/ * text_gc; } ;

/* Variables and functions */
 int GCBackground ; 
 int GCForeground ; 
 int GCFunction ; 
 int /*<<< orphan*/  GXxor ; 
 int /*<<< orphan*/  XChangeGC (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,TYPE_1__*) ; 
 TYPE_2__ gui ; 
 int /*<<< orphan*/  gui_x11_set_back_color () ; 

void
gui_mch_new_colors()
{
    long_u	gc_mask;
    XGCValues	gc_vals;

    gc_mask = GCForeground | GCBackground;
    gc_vals.foreground = gui.norm_pixel;
    gc_vals.background = gui.back_pixel;
    if (gui.text_gc != NULL)
	XChangeGC(gui.dpy, gui.text_gc, gc_mask, &gc_vals);

    gc_vals.foreground = gui.back_pixel;
    gc_vals.background = gui.norm_pixel;
    if (gui.back_gc != NULL)
	XChangeGC(gui.dpy, gui.back_gc, gc_mask, &gc_vals);

    gc_mask |= GCFunction;
    gc_vals.foreground = gui.norm_pixel ^ gui.back_pixel;
    gc_vals.background = gui.norm_pixel ^ gui.back_pixel;
    gc_vals.function   = GXxor;
    if (gui.invert_gc != NULL)
	XChangeGC(gui.dpy, gui.invert_gc, gc_mask, &gc_vals);

    gui_x11_set_back_color();
}