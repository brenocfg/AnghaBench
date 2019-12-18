#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* gint ;
struct TYPE_5__ {void* height; void* width; } ;
struct TYPE_6__ {TYPE_1__ requisition; } ;
typedef  TYPE_2__ GtkWidget ;
typedef  int /*<<< orphan*/  GtkForm ;

/* Variables and functions */
 int /*<<< orphan*/  gtk_form_move (int /*<<< orphan*/ *,TYPE_2__*,void*,void*) ; 

void
gtk_form_move_resize(GtkForm *form, GtkWidget *widget,
		     gint x, gint y, gint w, gint h)
{
    widget->requisition.width  = w;
    widget->requisition.height = h;

    gtk_form_move(form, widget, x, y);
}