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
 int /*<<< orphan*/  PLy_exc_error ; 
 int /*<<< orphan*/  PLy_exception_set (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * PLy_spi_execute_plan (int /*<<< orphan*/ *,int /*<<< orphan*/ *,long) ; 
 int /*<<< orphan*/ * PLy_spi_execute_query (char*,long) ; 
 scalar_t__ PyArg_ParseTuple (int /*<<< orphan*/ *,char*,char**,long*,...) ; 
 int /*<<< orphan*/  PyErr_Clear () ; 
 scalar_t__ is_PLyPlanObject (int /*<<< orphan*/ *) ; 

PyObject *
PLy_spi_execute(PyObject *self, PyObject *args)
{
	char	   *query;
	PyObject   *plan;
	PyObject   *list = NULL;
	long		limit = 0;

	if (PyArg_ParseTuple(args, "s|l", &query, &limit))
		return PLy_spi_execute_query(query, limit);

	PyErr_Clear();

	if (PyArg_ParseTuple(args, "O|Ol", &plan, &list, &limit) &&
		is_PLyPlanObject(plan))
		return PLy_spi_execute_plan(plan, list, limit);

	PLy_exception_set(PLy_exc_error, "plpy.execute expected a query or a plan");
	return NULL;
}