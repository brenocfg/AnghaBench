#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ freeze_count; } ;
typedef  TYPE_1__ GtkForm ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_IS_FORM (TYPE_1__*) ; 
 int /*<<< orphan*/  GTK_WIDGET (TYPE_1__*) ; 
 int /*<<< orphan*/  g_return_if_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_form_position_children (TYPE_1__*) ; 
 int /*<<< orphan*/  gtk_widget_queue_draw (int /*<<< orphan*/ ) ; 

void
gtk_form_thaw(GtkForm *form)
{
    g_return_if_fail(GTK_IS_FORM(form));

    if (form->freeze_count)
    {
	if (!(--form->freeze_count))
	{
	    gtk_form_position_children(form);
	    gtk_widget_queue_draw(GTK_WIDGET(form));
	}
    }
}