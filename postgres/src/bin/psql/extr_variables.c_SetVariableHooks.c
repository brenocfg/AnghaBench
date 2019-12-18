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
struct _variable {void* (* substitute_hook ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/ * value; struct _variable* next; int /*<<< orphan*/  (* assign_hook ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  name; } ;
typedef  void* (* VariableSubstituteHook ) (int /*<<< orphan*/ *) ;
typedef  struct _variable* VariableSpace ;
typedef  int /*<<< orphan*/  (* VariableAssignHook ) (int /*<<< orphan*/ *) ;

/* Variables and functions */
 struct _variable* pg_malloc (int) ; 
 int /*<<< orphan*/  pg_strdup (char const*) ; 
 int strcmp (int /*<<< orphan*/ ,char const*) ; 
 void* stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *) ; 
 void* stub3 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  valid_variable_name (char const*) ; 

void
SetVariableHooks(VariableSpace space, const char *name,
				 VariableSubstituteHook shook,
				 VariableAssignHook ahook)
{
	struct _variable *current,
			   *previous;

	if (!space || !name)
		return;

	if (!valid_variable_name(name))
		return;

	for (previous = space, current = space->next;
		 current;
		 previous = current, current = current->next)
	{
		int			cmp = strcmp(current->name, name);

		if (cmp == 0)
		{
			/* found entry, so update */
			current->substitute_hook = shook;
			current->assign_hook = ahook;
			if (shook)
				current->value = (*shook) (current->value);
			if (ahook)
				(void) (*ahook) (current->value);
			return;
		}
		if (cmp > 0)
			break;				/* it's not there */
	}

	/* not present, make new entry */
	current = pg_malloc(sizeof *current);
	current->name = pg_strdup(name);
	current->value = NULL;
	current->substitute_hook = shook;
	current->assign_hook = ahook;
	current->next = previous->next;
	previous->next = current;
	if (shook)
		current->value = (*shook) (current->value);
	if (ahook)
		(void) (*ahook) (current->value);
}