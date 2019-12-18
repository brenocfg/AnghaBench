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
struct TYPE_5__ {TYPE_1__* tail; TYPE_1__* head; } ;
struct TYPE_4__ {struct TYPE_4__* next; int /*<<< orphan*/  val; } ;
typedef  TYPE_1__ SimpleOidListCell ;
typedef  TYPE_2__ SimpleOidList ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 scalar_t__ pg_malloc (int) ; 

void
simple_oid_list_append(SimpleOidList *list, Oid val)
{
	SimpleOidListCell *cell;

	cell = (SimpleOidListCell *) pg_malloc(sizeof(SimpleOidListCell));
	cell->next = NULL;
	cell->val = val;

	if (list->tail)
		list->tail->next = cell;
	else
		list->head = cell;
	list->tail = cell;
}