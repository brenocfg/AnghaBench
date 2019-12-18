#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct list_head {struct list_head* next; struct list_head* prev; } ;

/* Variables and functions */
 scalar_t__ CHECK_DATA_CORRUPTION (int,char*,struct list_head*,struct list_head*,struct list_head*) ; 

bool __list_add_valid(struct list_head *new, struct list_head *prev,
		      struct list_head *next)
{
	if (CHECK_DATA_CORRUPTION(next->prev != prev,
			"list_add corruption. next->prev should be prev (%px), but was %px. (next=%px).\n",
			prev, next->prev, next) ||
	    CHECK_DATA_CORRUPTION(prev->next != next,
			"list_add corruption. prev->next should be next (%px), but was %px. (prev=%px).\n",
			next, prev->next, prev) ||
	    CHECK_DATA_CORRUPTION(new == prev || new == next,
			"list_add double add: new=%px, prev=%px, next=%px.\n",
			new, prev, next))
		return false;

	return true;
}