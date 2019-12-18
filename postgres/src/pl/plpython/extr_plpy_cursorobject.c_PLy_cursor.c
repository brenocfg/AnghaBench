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
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/ * PLy_cursor_plan (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PLy_cursor_query (char*) ; 
 int /*<<< orphan*/  PLy_exc_error ; 
 int /*<<< orphan*/  PLy_exception_set (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ PyArg_ParseTuple (int /*<<< orphan*/ *,char*,char**,...) ; 
 int /*<<< orphan*/  PyErr_Clear () ; 

PyObject *
PLy_cursor(PyObject *self, PyObject *args)
{
	char	   *query;
	PyObject   *plan;
	PyObject   *planargs = NULL;

	if (PyArg_ParseTuple(args, "s", &query))
		return PLy_cursor_query(query);

	PyErr_Clear();

	if (PyArg_ParseTuple(args, "O|O", &plan, &planargs))
		return PLy_cursor_plan(plan, planargs);

	PLy_exception_set(PLy_exc_error, "plpy.cursor expected a query or a plan");
	return NULL;
}