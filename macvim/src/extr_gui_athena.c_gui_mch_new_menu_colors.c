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
struct TYPE_2__ {scalar_t__ menu_fg_pixel; } ;

/* Variables and functions */
 scalar_t__ INVALCOLOR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  XtNborderColor ; 
 int /*<<< orphan*/  XtVaSetValues (scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 TYPE_1__ gui ; 
 int /*<<< orphan*/  gui_athena_menu_colors (scalar_t__) ; 
 int /*<<< orphan*/  gui_mch_submenu_change (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ menuBar ; 
 int /*<<< orphan*/  root_menu ; 
 scalar_t__ toolBar ; 

void
gui_mch_new_menu_colors()
{
    if (menuBar == (Widget)0)
	return;
    if (gui.menu_fg_pixel != INVALCOLOR)
	XtVaSetValues(menuBar, XtNborderColor,	gui.menu_fg_pixel, NULL);
    gui_athena_menu_colors(menuBar);
#ifdef FEAT_TOOLBAR
    gui_athena_menu_colors(toolBar);
#endif

    gui_mch_submenu_change(root_menu, TRUE);
}