#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* name; } ;
typedef  TYPE_1__ Variable ;
struct TYPE_6__ {int vars_sorted; int /*<<< orphan*/  nvariables; scalar_t__ variables; } ;
typedef  TYPE_2__ CState ;

/* Variables and functions */
 scalar_t__ bsearch (void*,void*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compareVariableNames ; 
 int /*<<< orphan*/  qsort (void*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Variable *
lookupVariable(CState *st, char *name)
{
	Variable	key;

	/* On some versions of Solaris, bsearch of zero items dumps core */
	if (st->nvariables <= 0)
		return NULL;

	/* Sort if we have to */
	if (!st->vars_sorted)
	{
		qsort((void *) st->variables, st->nvariables, sizeof(Variable),
			  compareVariableNames);
		st->vars_sorted = true;
	}

	/* Now we can search */
	key.name = name;
	return (Variable *) bsearch((void *) &key,
								(void *) st->variables,
								st->nvariables,
								sizeof(Variable),
								compareVariableNames);
}