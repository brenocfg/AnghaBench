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
struct variable {int brace_level; struct variable* next; struct variable* name; int /*<<< orphan*/  type; } ;
struct cursor {struct arguments* argsresult; struct arguments* argsinsert; struct cursor* next; } ;
struct arguments {struct arguments* next; struct variable* variable; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECPGfree_type (int /*<<< orphan*/ ) ; 
 struct variable* allvariables ; 
 struct cursor* cur ; 
 int /*<<< orphan*/  free (struct variable*) ; 

void
remove_variables(int brace_level)
{
	struct variable *p,
			   *prev;

	for (p = prev = allvariables; p;)
	{
		if (p->brace_level >= brace_level)
		{
			/* is it still referenced by a cursor? */
			struct cursor *ptr;

			for (ptr = cur; ptr != NULL; ptr = ptr->next)
			{
				struct arguments *varptr,
						   *prevvar;

				for (varptr = prevvar = ptr->argsinsert; varptr != NULL; varptr = varptr->next)
				{
					if (p == varptr->variable)
					{
						/* remove from list */
						if (varptr == ptr->argsinsert)
							ptr->argsinsert = varptr->next;
						else
							prevvar->next = varptr->next;
					}
				}
				for (varptr = prevvar = ptr->argsresult; varptr != NULL; varptr = varptr->next)
				{
					if (p == varptr->variable)
					{
						/* remove from list */
						if (varptr == ptr->argsresult)
							ptr->argsresult = varptr->next;
						else
							prevvar->next = varptr->next;
					}
				}
			}

			/* remove it */
			if (p == allvariables)
				prev = allvariables = p->next;
			else
				prev->next = p->next;

			ECPGfree_type(p->type);
			free(p->name);
			free(p);
			if (prev == allvariables)
				p = allvariables;
			else
				p = prev ? prev->next : NULL;
		}
		else
		{
			prev = p;
			p = prev->next;
		}
	}
}