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
typedef  int gint ;
typedef  int /*<<< orphan*/  GtkButton ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GTK_PANED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GTK_WINDOW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPLIT_VIEW ; 
 int /*<<< orphan*/  back_btn ; 
 int /*<<< orphan*/  display_list () ; 
 int /*<<< orphan*/  gtk_paned_set_position (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gtk_tree_store_clear (scalar_t__) ; 
 int /*<<< orphan*/  gtk_widget_set_sensitive (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_show (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_window_get_default_size (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  hpaned ; 
 int /*<<< orphan*/  main_wnd ; 
 int /*<<< orphan*/  tree1_w ; 
 scalar_t__ tree2 ; 
 int /*<<< orphan*/  view_mode ; 

void on_split_clicked(GtkButton * button, gpointer user_data)
{
	gint w, h;
	view_mode = SPLIT_VIEW;
	gtk_widget_show(tree1_w);
	gtk_window_get_default_size(GTK_WINDOW(main_wnd), &w, &h);
	gtk_paned_set_position(GTK_PANED(hpaned), w / 2);
	if (tree2)
		gtk_tree_store_clear(tree2);
	display_list();

	/* Disable back btn, like in full mode. */
	gtk_widget_set_sensitive(back_btn, FALSE);
}