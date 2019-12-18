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
 int /*<<< orphan*/  PyArg_ParseTuple (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **) ; 

__attribute__((used)) static PyObject *
PLy_plan_cursor(PyObject *self, PyObject *args)
{
	PyObject   *planargs = NULL;

	if (!PyArg_ParseTuple(args, "|O", &planargs))
		return NULL;

	return PLy_cursor_plan(self, planargs);
}