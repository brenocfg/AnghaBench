#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int nargs; int /*<<< orphan*/  args; int /*<<< orphan*/ * namedargs; } ;
typedef  TYPE_1__ PLySavedArgs ;

/* Variables and functions */
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 

__attribute__((used)) static void
PLy_function_drop_args(PLySavedArgs *savedargs)
{
	int			i;

	/* Drop references for named args */
	for (i = 0; i < savedargs->nargs; i++)
	{
		Py_XDECREF(savedargs->namedargs[i]);
	}

	/* Drop ref to the "args" object, too */
	Py_XDECREF(savedargs->args);

	/* And free the PLySavedArgs struct */
	pfree(savedargs);
}