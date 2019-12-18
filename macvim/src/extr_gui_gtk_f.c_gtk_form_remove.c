#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {struct TYPE_13__* next; TYPE_1__* data; } ;
struct TYPE_12__ {TYPE_3__* children; } ;
struct TYPE_11__ {scalar_t__ window; int /*<<< orphan*/ * widget; } ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  TYPE_1__ GtkFormChild ;
typedef  TYPE_2__ GtkForm ;
typedef  int /*<<< orphan*/  GtkContainer ;
typedef  TYPE_3__ GList ;

/* Variables and functions */
 TYPE_2__* GTK_FORM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_IS_FORM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_OBJECT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_SIGNAL_FUNC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (TYPE_1__*) ; 
 int /*<<< orphan*/  g_list_free_1 (TYPE_3__*) ; 
 TYPE_3__* g_list_remove_link (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  g_return_if_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdk_window_destroy (scalar_t__) ; 
 int /*<<< orphan*/  gdk_window_set_user_data (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_form_child_map ; 
 int /*<<< orphan*/  gtk_form_child_unmap ; 
 int /*<<< orphan*/  gtk_signal_disconnect_by_func (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  gtk_widget_unparent (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
gtk_form_remove(GtkContainer *container, GtkWidget *widget)
{
    GList *tmp_list;
    GtkForm *form;
    GtkFormChild *child = NULL;	    /* init for gcc */

    g_return_if_fail(GTK_IS_FORM(container));

    form = GTK_FORM(container);

    tmp_list = form->children;
    while (tmp_list)
    {
	child = tmp_list->data;
	if (child->widget == widget)
	    break;
	tmp_list = tmp_list->next;
    }

    if (tmp_list)
    {
	if (child->window)
	{
	    gtk_signal_disconnect_by_func(GTK_OBJECT(child->widget),
					  GTK_SIGNAL_FUNC(&gtk_form_child_map), child);
	    gtk_signal_disconnect_by_func(GTK_OBJECT(child->widget),
					  GTK_SIGNAL_FUNC(&gtk_form_child_unmap), child);

	    /* FIXME: This will cause problems for reparenting NO_WINDOW
	     * widgets out of a GtkForm
	     */
	    gdk_window_set_user_data(child->window, NULL);
	    gdk_window_destroy(child->window);
	}
	gtk_widget_unparent(widget);

	form->children = g_list_remove_link(form->children, tmp_list);
	g_list_free_1(tmp_list);
	g_free(child);
    }
}