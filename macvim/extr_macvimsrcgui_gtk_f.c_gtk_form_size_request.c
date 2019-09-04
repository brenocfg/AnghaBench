#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {struct TYPE_10__* next; TYPE_2__* data; } ;
struct TYPE_9__ {TYPE_4__* children; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_8__ {int /*<<< orphan*/  widget; } ;
struct TYPE_7__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  TYPE_1__ GtkRequisition ;
typedef  TYPE_2__ GtkFormChild ;
typedef  TYPE_3__ GtkForm ;
typedef  TYPE_4__ GList ;

/* Variables and functions */
 TYPE_3__* GTK_FORM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_IS_FORM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_return_if_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_size_request (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
gtk_form_size_request(GtkWidget *widget, GtkRequisition *requisition)
{
    GList *tmp_list;
    GtkForm *form;

    g_return_if_fail(GTK_IS_FORM(widget));

    form = GTK_FORM(widget);

    requisition->width = form->width;
    requisition->height = form->height;

    tmp_list = form->children;

    while (tmp_list)
    {
	GtkFormChild *child = tmp_list->data;
	gtk_widget_size_request(child->widget, NULL);
	tmp_list = tmp_list->next;
    }
}