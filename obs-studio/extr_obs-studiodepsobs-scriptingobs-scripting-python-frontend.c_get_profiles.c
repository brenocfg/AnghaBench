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
 int /*<<< orphan*/  PyList_Append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyList_New (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PyUnicode_FromString (char*) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfree (char**) ; 
 char** obs_frontend_get_profiles () ; 

__attribute__((used)) static PyObject *get_profiles(PyObject *self, PyObject *args)
{
	char **names = obs_frontend_get_profiles();
	char **name = names;

	PyObject *list = PyList_New(0);

	while (name && *name) {
		PyObject *py_name = PyUnicode_FromString(*name);
		if (py_name) {
			PyList_Append(list, py_name);
			Py_DECREF(py_name);
		}
		name++;
	}

	UNUSED_PARAMETER(self);
	UNUSED_PARAMETER(args);

	bfree(names);
	return list;
}