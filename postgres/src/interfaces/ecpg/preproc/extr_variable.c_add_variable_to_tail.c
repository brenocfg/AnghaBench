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
struct arguments {struct arguments* next; struct variable* indicator; struct variable* variable; } ;

/* Variables and functions */
 scalar_t__ mm_alloc (int) ; 

void
add_variable_to_tail(struct arguments **list, struct variable *var, struct variable *ind)
{
	struct arguments *p,
			   *new = (struct arguments *) mm_alloc(sizeof(struct arguments));

	for (p = *list; p && p->next; p = p->next);

	new->variable = var;
	new->indicator = ind;
	new->next = NULL;

	if (p)
		p->next = new;
	else
		*list = new;
}