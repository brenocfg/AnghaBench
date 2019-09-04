#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_2__* data; struct TYPE_13__* next; } ;
struct TYPE_12__ {TYPE_4__* children; int /*<<< orphan*/  bin_window; } ;
struct TYPE_11__ {int /*<<< orphan*/  widget; } ;
struct TYPE_10__ {int /*<<< orphan*/  window; } ;
typedef  TYPE_1__ GtkWidget ;
typedef  TYPE_2__ GtkFormChild ;
typedef  TYPE_3__ GtkForm ;
typedef  TYPE_4__ GList ;

/* Variables and functions */
 TYPE_3__* GTK_FORM (TYPE_1__*) ; 
 int /*<<< orphan*/  GTK_IS_FORM (TYPE_1__*) ; 
 int /*<<< orphan*/  GTK_MAPPED ; 
 int /*<<< orphan*/  GTK_WIDGET_MAPPED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GTK_WIDGET_SET_FLAGS (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ GTK_WIDGET_VISIBLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_return_if_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdk_window_show (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_map (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gtk_form_map(GtkWidget *widget)
{
    GList *tmp_list;
    GtkForm *form;

    g_return_if_fail(GTK_IS_FORM(widget));

    form = GTK_FORM(widget);

    GTK_WIDGET_SET_FLAGS(widget, GTK_MAPPED);

    gdk_window_show(widget->window);
    gdk_window_show(form->bin_window);

    for (tmp_list = form->children; tmp_list; tmp_list = tmp_list->next)
    {
	GtkFormChild *child = tmp_list->data;

	if (GTK_WIDGET_VISIBLE(child->widget)
		&& !GTK_WIDGET_MAPPED(child->widget))
	    gtk_widget_map(child->widget);
    }
}