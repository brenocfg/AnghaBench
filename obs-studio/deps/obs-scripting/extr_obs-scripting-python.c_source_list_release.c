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
typedef  scalar_t__ Py_ssize_t ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/ * PyList_GetItem (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ PyList_Size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_source_release (int) ; 
 int obs_source_t ; 
 int /*<<< orphan*/  parse_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **) ; 
 scalar_t__ py_to_libobs (int,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/ * python_none () ; 
 int source ; 

__attribute__((used)) static PyObject *source_list_release(PyObject *self, PyObject *args)
{
	PyObject *list;
	if (!parse_args(args, "O", &list))
		return python_none();

	Py_ssize_t count = PyList_Size(list);
	for (Py_ssize_t i = 0; i < count; i++) {
		PyObject *py_source = PyList_GetItem(list, i);
		obs_source_t *source;

		if (py_to_libobs(obs_source_t, py_source, &source)) {
			obs_source_release(source);
		}
	}

	UNUSED_PARAMETER(self);
	return python_none();
}