#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  rows; } ;
typedef  int /*<<< orphan*/  Py_ssize_t ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ PLyResultObject ;

/* Variables and functions */
 int /*<<< orphan*/ * PyList_GetItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyObject *
PLy_result_item(PyObject *arg, Py_ssize_t idx)
{
	PyObject   *rv;
	PLyResultObject *ob = (PLyResultObject *) arg;

	rv = PyList_GetItem(ob->rows, idx);
	if (rv != NULL)
		Py_INCREF(rv);
	return rv;
}