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
struct TYPE_5__ {TYPE_1__* head; } ;
struct TYPE_4__ {scalar_t__ val; struct TYPE_4__* next; } ;
typedef  TYPE_1__ SimpleOidListCell ;
typedef  TYPE_2__ SimpleOidList ;
typedef  scalar_t__ Oid ;

/* Variables and functions */

bool
simple_oid_list_member(SimpleOidList *list, Oid val)
{
	SimpleOidListCell *cell;

	for (cell = list->head; cell; cell = cell->next)
	{
		if (cell->val == val)
			return true;
	}
	return false;
}