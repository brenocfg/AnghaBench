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
typedef  int /*<<< orphan*/  gpointer ;
struct TYPE_2__ {int /*<<< orphan*/  cancel_button; int /*<<< orphan*/  ok_button; } ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GtkMenuItem ;

/* Variables and functions */
 TYPE_1__* GTK_FILE_SELECTION (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_OBJECT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_CALLBACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_signal_connect (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_signal_connect_swapped (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_file_selection_new (char*) ; 
 int /*<<< orphan*/  gtk_widget_destroy ; 
 int /*<<< orphan*/  gtk_widget_show (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  load_filename ; 

void on_load1_activate(GtkMenuItem * menuitem, gpointer user_data)
{
	GtkWidget *fs;

	fs = gtk_file_selection_new("Load file...");
	g_signal_connect(GTK_OBJECT(GTK_FILE_SELECTION(fs)->ok_button),
			 "clicked",
			 G_CALLBACK(load_filename), (gpointer) fs);
	g_signal_connect_swapped(GTK_OBJECT
				 (GTK_FILE_SELECTION(fs)->ok_button),
				 "clicked", G_CALLBACK(gtk_widget_destroy),
				 (gpointer) fs);
	g_signal_connect_swapped(GTK_OBJECT
				 (GTK_FILE_SELECTION(fs)->cancel_button),
				 "clicked", G_CALLBACK(gtk_widget_destroy),
				 (gpointer) fs);
	gtk_widget_show(fs);
}