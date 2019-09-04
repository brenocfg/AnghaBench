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
typedef  int /*<<< orphan*/  gpointer ;
typedef  int /*<<< orphan*/  GtkMenuItem ;

/* Variables and functions */
 int /*<<< orphan*/  OPT_ALL ; 
 int /*<<< orphan*/  display_tree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_store_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opt_mode ; 
 int /*<<< orphan*/  rootmenu ; 
 int /*<<< orphan*/  tree2 ; 

void
on_set_option_mode2_activate(GtkMenuItem *menuitem, gpointer user_data)
{
	opt_mode = OPT_ALL;
	gtk_tree_store_clear(tree2);
	display_tree(&rootmenu);	/* instead of update_tree to speed-up */
}