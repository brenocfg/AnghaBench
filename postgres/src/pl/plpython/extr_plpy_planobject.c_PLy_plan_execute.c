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
 int /*<<< orphan*/ * PLy_spi_execute_plan (int /*<<< orphan*/ *,int /*<<< orphan*/ *,long) ; 
 int /*<<< orphan*/  PyArg_ParseTuple (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **,long*) ; 

__attribute__((used)) static PyObject *
PLy_plan_execute(PyObject *self, PyObject *args)
{
	PyObject   *list = NULL;
	long		limit = 0;

	if (!PyArg_ParseTuple(args, "|Ol", &list, &limit))
		return NULL;

	return PLy_spi_execute_plan(self, list, limit);
}