#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int gboolean ;
struct TYPE_16__ {struct TYPE_16__* next; int /*<<< orphan*/ * data; } ;
struct TYPE_15__ {scalar_t__ x; scalar_t__ y; scalar_t__ width; scalar_t__ height; } ;
struct TYPE_14__ {int /*<<< orphan*/  bin_window; TYPE_4__* children; } ;
struct TYPE_13__ {TYPE_3__ allocation; int /*<<< orphan*/  window; } ;
typedef  TYPE_1__ GtkWidget ;
typedef  int /*<<< orphan*/  GtkFormChild ;
typedef  TYPE_2__ GtkForm ;
typedef  TYPE_3__ GtkAllocation ;
typedef  TYPE_4__ GList ;

/* Variables and functions */
 TYPE_2__* GTK_FORM (TYPE_1__*) ; 
 int /*<<< orphan*/  GTK_IS_FORM (TYPE_1__*) ; 
 scalar_t__ GTK_WIDGET_REALIZED (TYPE_1__*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_return_if_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdk_window_move_resize (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gtk_form_position_child (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_form_send_configure (TYPE_2__*) ; 

__attribute__((used)) static void
gtk_form_size_allocate(GtkWidget *widget, GtkAllocation *allocation)
{
    GList *tmp_list;
    GtkForm *form;
    gboolean need_reposition;

    g_return_if_fail(GTK_IS_FORM(widget));

    if (widget->allocation.x == allocation->x
	    && widget->allocation.y == allocation->y
	    && widget->allocation.width == allocation->width
	    && widget->allocation.height == allocation->height)
	return;

    need_reposition = widget->allocation.width != allocation->width
		   || widget->allocation.height != allocation->height;
    form = GTK_FORM(widget);

    if (need_reposition)
    {
	tmp_list = form->children;

	while (tmp_list)
	{
	    GtkFormChild *child = tmp_list->data;
	    gtk_form_position_child(form, child, TRUE);

	    tmp_list = tmp_list->next;
	}
    }

    if (GTK_WIDGET_REALIZED(widget))
    {
	gdk_window_move_resize(widget->window,
			       allocation->x, allocation->y,
			       allocation->width, allocation->height);
	gdk_window_move_resize(GTK_FORM(widget)->bin_window,
			       0, 0,
			       allocation->width, allocation->height);
    }
    widget->allocation = *allocation;
    if (need_reposition)
	gtk_form_send_configure(form);
}