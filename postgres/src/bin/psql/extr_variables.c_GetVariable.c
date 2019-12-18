#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct _variable {char const* value; int /*<<< orphan*/  name; struct _variable* next; } ;
typedef  TYPE_1__* VariableSpace ;
struct TYPE_3__ {struct _variable* next; } ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ ,char const*) ; 

const char *
GetVariable(VariableSpace space, const char *name)
{
	struct _variable *current;

	if (!space)
		return NULL;

	for (current = space->next; current; current = current->next)
	{
		int			cmp = strcmp(current->name, name);

		if (cmp == 0)
		{
			/* this is correct answer when value is NULL, too */
			return current->value;
		}
		if (cmp > 0)
			break;				/* it's not there */
	}

	return NULL;
}