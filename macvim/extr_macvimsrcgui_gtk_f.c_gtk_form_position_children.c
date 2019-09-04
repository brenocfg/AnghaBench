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
struct TYPE_6__ {int /*<<< orphan*/  data; struct TYPE_6__* next; } ;
struct TYPE_5__ {TYPE_2__* children; } ;
typedef  TYPE_1__ GtkForm ;
typedef  TYPE_2__ GList ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  gtk_form_position_child (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gtk_form_position_children(GtkForm *form)
{
    GList *tmp_list;

    for (tmp_list = form->children; tmp_list; tmp_list = tmp_list->next)
	gtk_form_position_child(form, tmp_list->data, FALSE);
}