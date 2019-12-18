#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ Widget ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  gui_motif_menu_colors (scalar_t__) ; 
 scalar_t__ menuBar ; 
 int /*<<< orphan*/  root_menu ; 
 int /*<<< orphan*/  submenu_change (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ toolBar ; 
 scalar_t__ toolBarFrame ; 

void
gui_mch_new_menu_colors()
{
    if (menuBar == (Widget)0)
	return;
    gui_motif_menu_colors(menuBar);
#ifdef FEAT_TOOLBAR
    gui_motif_menu_colors(toolBarFrame);
    gui_motif_menu_colors(toolBar);
#endif

    submenu_change(root_menu, TRUE);
}