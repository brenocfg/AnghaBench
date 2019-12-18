#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int gint ;
struct TYPE_19__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_24__ {TYPE_1__ requisition; } ;
struct TYPE_23__ {int /*<<< orphan*/  event_mask; int /*<<< orphan*/  colormap; int /*<<< orphan*/  visual; int /*<<< orphan*/  wclass; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  window_type; } ;
struct TYPE_22__ {int /*<<< orphan*/ * bin_window; } ;
struct TYPE_21__ {TYPE_6__* widget; int /*<<< orphan*/ * window; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_20__ {int /*<<< orphan*/  style; } ;
typedef  TYPE_2__ GtkWidget ;
typedef  TYPE_3__ GtkFormChild ;
typedef  TYPE_4__ GtkForm ;
typedef  TYPE_5__ GdkWindowAttr ;

/* Variables and functions */
 int /*<<< orphan*/  GDK_EXPOSURE_MASK ; 
 int /*<<< orphan*/  GDK_INPUT_OUTPUT ; 
 int GDK_WA_COLORMAP ; 
 int GDK_WA_VISUAL ; 
 int GDK_WA_X ; 
 int GDK_WA_Y ; 
 int /*<<< orphan*/  GDK_WINDOW_CHILD ; 
 int /*<<< orphan*/  GTK_OBJECT (TYPE_6__*) ; 
 int /*<<< orphan*/  GTK_SIGNAL_FUNC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_STATE_NORMAL ; 
 TYPE_2__* GTK_WIDGET (TYPE_4__*) ; 
 scalar_t__ GTK_WIDGET_NO_WINDOW (TYPE_6__*) ; 
 int /*<<< orphan*/  GTK_WIDGET_REALIZED (TYPE_6__*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * gdk_window_new (int /*<<< orphan*/ *,TYPE_5__*,int) ; 
 int /*<<< orphan*/  gdk_window_set_user_data (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  gtk_form_child_map ; 
 int /*<<< orphan*/  gtk_form_child_unmap ; 
 int /*<<< orphan*/  gtk_form_set_static_gravity (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_signal_connect (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  gtk_style_set_background (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_get_colormap (TYPE_2__*) ; 
 int /*<<< orphan*/  gtk_widget_get_visual (TYPE_2__*) ; 
 int /*<<< orphan*/  gtk_widget_set_parent_window (TYPE_6__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
gtk_form_attach_child_window(GtkForm *form, GtkFormChild *child)
{
    if (child->window != NULL)
	return; /* been there, done that */

    if (GTK_WIDGET_NO_WINDOW(child->widget))
    {
	GtkWidget	*widget;
	GdkWindowAttr	attributes;
	gint		attributes_mask;

	widget = GTK_WIDGET(form);

	attributes.window_type = GDK_WINDOW_CHILD;
	attributes.x = child->x;
	attributes.y = child->y;
	attributes.width = child->widget->requisition.width;
	attributes.height = child->widget->requisition.height;
	attributes.wclass = GDK_INPUT_OUTPUT;
	attributes.visual = gtk_widget_get_visual(widget);
	attributes.colormap = gtk_widget_get_colormap(widget);
	attributes.event_mask = GDK_EXPOSURE_MASK;

	attributes_mask = GDK_WA_X | GDK_WA_Y | GDK_WA_VISUAL | GDK_WA_COLORMAP;
	child->window = gdk_window_new(form->bin_window,
				       &attributes, attributes_mask);
	gdk_window_set_user_data(child->window, widget);

	gtk_style_set_background(widget->style,
				 child->window,
				 GTK_STATE_NORMAL);

	gtk_widget_set_parent_window(child->widget, child->window);
	gtk_form_set_static_gravity(child->window, TRUE);
	/*
	 * Install signal handlers to map/unmap child->window
	 * alongside with the actual widget.
	 */
	gtk_signal_connect(GTK_OBJECT(child->widget), "map",
			   GTK_SIGNAL_FUNC(&gtk_form_child_map), child);
	gtk_signal_connect(GTK_OBJECT(child->widget), "unmap",
			   GTK_SIGNAL_FUNC(&gtk_form_child_unmap), child);
    }
    else if (!GTK_WIDGET_REALIZED(child->widget))
    {
	gtk_widget_set_parent_window(child->widget, form->bin_window);
    }
}