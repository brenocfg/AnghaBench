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
struct variable {int dummy; } ;
struct arguments {struct arguments* next; struct variable* variable; } ;

/* Variables and functions */

void
remove_variable_from_list(struct arguments **list, struct variable *var)
{
	struct arguments *p,
			   *prev = NULL;
	bool		found = false;

	for (p = *list; p; p = p->next)
	{
		if (p->variable == var)
		{
			found = true;
			break;
		}
		prev = p;
	}
	if (found)
	{
		if (prev)
			prev->next = p->next;
		else
			*list = p->next;
	}
}