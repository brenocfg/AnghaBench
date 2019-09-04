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
typedef  scalar_t__ Widget ;
struct TYPE_2__ {int /*<<< orphan*/ * dpy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XtCloseDisplay (int /*<<< orphan*/ *) ; 
 TYPE_1__ gui ; 
 int /*<<< orphan*/ * gui_argv ; 
 int /*<<< orphan*/  gui_x11_destroy_widgets () ; 
 scalar_t__ vimShell ; 
 int /*<<< orphan*/  vim_free (int /*<<< orphan*/ *) ; 

void
gui_mch_uninit()
{
    gui_x11_destroy_widgets();
    XtCloseDisplay(gui.dpy);
    gui.dpy = NULL;
    vimShell = (Widget)0;
    vim_free(gui_argv);
    gui_argv = NULL;
}