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
struct TYPE_4__ {int pointer_hidden; TYPE_1__* drawarea; int /*<<< orphan*/ * blank_pointer; } ;
struct TYPE_3__ {scalar_t__ window; } ;

/* Variables and functions */
 int /*<<< orphan*/  gdk_window_set_cursor (scalar_t__,int /*<<< orphan*/ *) ; 
 TYPE_2__ gui ; 
 int /*<<< orphan*/  last_shape ; 
 int /*<<< orphan*/  mch_set_mouse_shape (int /*<<< orphan*/ ) ; 

void
gui_mch_mousehide(int hide)
{
    if (gui.pointer_hidden != hide)
    {
	gui.pointer_hidden = hide;
	if (gui.drawarea->window && gui.blank_pointer != NULL)
	{
	    if (hide)
		gdk_window_set_cursor(gui.drawarea->window, gui.blank_pointer);
	    else
#ifdef FEAT_MOUSESHAPE
		mch_set_mouse_shape(last_shape);
#else
		gdk_window_set_cursor(gui.drawarea->window, NULL);
#endif
	}
    }
}