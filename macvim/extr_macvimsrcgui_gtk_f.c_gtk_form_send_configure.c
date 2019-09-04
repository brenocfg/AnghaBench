#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  window; int /*<<< orphan*/  type; } ;
struct TYPE_5__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_6__ {TYPE_1__ allocation; int /*<<< orphan*/  window; } ;
typedef  TYPE_2__ GtkWidget ;
typedef  int /*<<< orphan*/  GtkForm ;
typedef  TYPE_3__ GdkEventConfigure ;
typedef  int /*<<< orphan*/  GdkEvent ;

/* Variables and functions */
 int /*<<< orphan*/  GDK_CONFIGURE ; 
 TYPE_2__* GTK_WIDGET (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_main_do_event (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
gtk_form_send_configure(GtkForm *form)
{
    GtkWidget *widget;
    GdkEventConfigure event;

    widget = GTK_WIDGET(form);

    event.type = GDK_CONFIGURE;
    event.window = widget->window;
    event.x = widget->allocation.x;
    event.y = widget->allocation.y;
    event.width = widget->allocation.width;
    event.height = widget->allocation.height;

    gtk_main_do_event((GdkEvent*)&event);
}