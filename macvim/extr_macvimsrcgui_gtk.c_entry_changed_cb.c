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
typedef  char gchar ;
typedef  int gboolean ;
struct TYPE_4__ {int /*<<< orphan*/  find; int /*<<< orphan*/ * dialog; } ;
struct TYPE_3__ {int /*<<< orphan*/  all; int /*<<< orphan*/  replace; int /*<<< orphan*/  find; int /*<<< orphan*/ * dialog; } ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_ENTRY (int /*<<< orphan*/ *) ; 
 TYPE_2__ find_widgets ; 
 char* gtk_entry_get_text (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_set_sensitive (int /*<<< orphan*/ ,int) ; 
 TYPE_1__ repl_widgets ; 

__attribute__((used)) static void
entry_changed_cb(GtkWidget * entry, GtkWidget * dialog)
{
    const gchar	*entry_text;
    gboolean	nonempty;

    entry_text = gtk_entry_get_text(GTK_ENTRY(entry));

    if (!entry_text)
	return;			/* shouldn't happen */

    nonempty = (entry_text[0] != '\0');

    if (dialog == find_widgets.dialog)
    {
	gtk_widget_set_sensitive(find_widgets.find, nonempty);
    }

    if (dialog == repl_widgets.dialog)
    {
	gtk_widget_set_sensitive(repl_widgets.find, nonempty);
	gtk_widget_set_sensitive(repl_widgets.replace, nonempty);
	gtk_widget_set_sensitive(repl_widgets.all, nonempty);
    }
}