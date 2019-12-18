#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * svalue; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ Variable ;
struct TYPE_9__ {int nvariables; int vars_sorted; TYPE_1__* variables; } ;
typedef  TYPE_2__ CState ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char*) ; 
 TYPE_1__* lookupVariable (TYPE_2__*,char*) ; 
 scalar_t__ pg_malloc (int) ; 
 scalar_t__ pg_realloc (TYPE_1__*,int) ; 
 int /*<<< orphan*/  pg_strdup (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  valid_variable_name (char*) ; 

__attribute__((used)) static Variable *
lookupCreateVariable(CState *st, const char *context, char *name)
{
	Variable   *var;

	var = lookupVariable(st, name);
	if (var == NULL)
	{
		Variable   *newvars;

		/*
		 * Check for the name only when declaring a new variable to avoid
		 * overhead.
		 */
		if (!valid_variable_name(name))
		{
			fprintf(stderr, "%s: invalid variable name: \"%s\"\n",
					context, name);
			return NULL;
		}

		/* Create variable at the end of the array */
		if (st->variables)
			newvars = (Variable *) pg_realloc(st->variables,
											  (st->nvariables + 1) * sizeof(Variable));
		else
			newvars = (Variable *) pg_malloc(sizeof(Variable));

		st->variables = newvars;

		var = &newvars[st->nvariables];

		var->name = pg_strdup(name);
		var->svalue = NULL;
		/* caller is expected to initialize remaining fields */

		st->nvariables++;
		/* we don't re-sort the array till we have to */
		st->vars_sorted = false;
	}

	return var;
}