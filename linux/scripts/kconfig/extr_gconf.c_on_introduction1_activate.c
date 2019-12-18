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
typedef  char gchar ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GtkMenuItem ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_BUTTONS_CLOSE ; 
 int /*<<< orphan*/  GTK_DIALOG_DESTROY_WITH_PARENT ; 
 int /*<<< orphan*/  GTK_MESSAGE_INFO ; 
 int /*<<< orphan*/  GTK_OBJECT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_WINDOW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_CALLBACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_signal_connect_swapped (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_message_dialog_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  gtk_widget_destroy ; 
 int /*<<< orphan*/  gtk_widget_show_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  main_wnd ; 

void on_introduction1_activate(GtkMenuItem * menuitem, gpointer user_data)
{
	GtkWidget *dialog;
	const gchar *intro_text =
	    "Welcome to gkc, the GTK+ graphical configuration tool\n"
	    "For each option, a blank box indicates the feature is disabled, a\n"
	    "check indicates it is enabled, and a dot indicates that it is to\n"
	    "be compiled as a module.  Clicking on the box will cycle through the three states.\n"
	    "\n"
	    "If you do not see an option (e.g., a device driver) that you\n"
	    "believe should be present, try turning on Show All Options\n"
	    "under the Options menu.\n"
	    "Although there is no cross reference yet to help you figure out\n"
	    "what other options must be enabled to support the option you\n"
	    "are interested in, you can still view the help of a grayed-out\n"
	    "option.\n"
	    "\n"
	    "Toggling Show Debug Info under the Options menu will show \n"
	    "the dependencies, which you can then match by examining other options.";

	dialog = gtk_message_dialog_new(GTK_WINDOW(main_wnd),
					GTK_DIALOG_DESTROY_WITH_PARENT,
					GTK_MESSAGE_INFO,
					GTK_BUTTONS_CLOSE, "%s", intro_text);
	g_signal_connect_swapped(GTK_OBJECT(dialog), "response",
				 G_CALLBACK(gtk_widget_destroy),
				 GTK_OBJECT(dialog));
	gtk_widget_show_all(dialog);
}