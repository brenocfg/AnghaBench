#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  enum _actions { ____Placeholder__actions } _actions ;
struct TYPE_5__ {TYPE_1__* tail; TYPE_1__* head; } ;
struct TYPE_4__ {int action; struct TYPE_4__* next; int /*<<< orphan*/ * val; } ;
typedef  TYPE_1__ SimpleActionListCell ;
typedef  TYPE_2__ SimpleActionList ;

/* Variables and functions */
 scalar_t__ pg_malloc (int) ; 
 int /*<<< orphan*/ * pg_strdup (char const*) ; 

__attribute__((used)) static void
simple_action_list_append(SimpleActionList *list,
						  enum _actions action, const char *val)
{
	SimpleActionListCell *cell;

	cell = (SimpleActionListCell *) pg_malloc(sizeof(SimpleActionListCell));

	cell->next = NULL;
	cell->action = action;
	if (val)
		cell->val = pg_strdup(val);
	else
		cell->val = NULL;

	if (list->tail)
		list->tail->next = cell;
	else
		list->head = cell;
	list->tail = cell;
}