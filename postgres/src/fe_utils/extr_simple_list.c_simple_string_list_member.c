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
struct TYPE_4__ {int touched; int /*<<< orphan*/  val; struct TYPE_4__* next; } ;
typedef  TYPE_1__ SimpleStringListCell ;
typedef  TYPE_2__ SimpleStringList ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

bool
simple_string_list_member(SimpleStringList *list, const char *val)
{
	SimpleStringListCell *cell;

	for (cell = list->head; cell; cell = cell->next)
	{
		if (strcmp(cell->val, val) == 0)
		{
			cell->touched = true;
			return true;
		}
	}
	return false;
}