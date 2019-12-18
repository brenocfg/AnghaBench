#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  (* unrealize ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_9__ {struct TYPE_9__* next; TYPE_1__* data; } ;
struct TYPE_8__ {int /*<<< orphan*/ * bin_window; TYPE_3__* children; } ;
struct TYPE_7__ {int /*<<< orphan*/ * window; int /*<<< orphan*/  widget; } ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  TYPE_1__ GtkFormChild ;
typedef  TYPE_2__ GtkForm ;
typedef  TYPE_3__ GList ;

/* Variables and functions */
 TYPE_2__* GTK_FORM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_IS_FORM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_OBJECT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GTK_SIGNAL_FUNC (int /*<<< orphan*/ ) ; 
 TYPE_5__* GTK_WIDGET_CLASS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_return_if_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdk_window_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gdk_window_set_user_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_form_child_map ; 
 int /*<<< orphan*/  gtk_form_child_unmap ; 
 int /*<<< orphan*/  gtk_signal_disconnect_by_func (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  parent_class ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
gtk_form_unrealize(GtkWidget *widget)
{
    GList *tmp_list;
    GtkForm *form;

    g_return_if_fail(GTK_IS_FORM(widget));

    form = GTK_FORM(widget);

    tmp_list = form->children;

    gdk_window_set_user_data(form->bin_window, NULL);
    gdk_window_destroy(form->bin_window);
    form->bin_window = NULL;

    while (tmp_list)
    {
	GtkFormChild *child = tmp_list->data;

	if (child->window != NULL)
	{
	    gtk_signal_disconnect_by_func(GTK_OBJECT(child->widget),
					  GTK_SIGNAL_FUNC(gtk_form_child_map),
					  child);
	    gtk_signal_disconnect_by_func(GTK_OBJECT(child->widget),
					  GTK_SIGNAL_FUNC(gtk_form_child_unmap),
					  child);

	    gdk_window_set_user_data(child->window, NULL);
	    gdk_window_destroy(child->window);

	    child->window = NULL;
	}

	tmp_list = tmp_list->next;
    }

    if (GTK_WIDGET_CLASS (parent_class)->unrealize)
	 (* GTK_WIDGET_CLASS (parent_class)->unrealize) (widget);
}