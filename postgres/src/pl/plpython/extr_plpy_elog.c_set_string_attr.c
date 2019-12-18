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
 int PyObject_SetAttrString (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyString_FromString (char*) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_None ; 

__attribute__((used)) static bool
set_string_attr(PyObject *obj, char *attrname, char *str)
{
	int			result;
	PyObject   *val;

	if (str != NULL)
	{
		val = PyString_FromString(str);
		if (!val)
			return false;
	}
	else
	{
		val = Py_None;
		Py_INCREF(Py_None);
	}

	result = PyObject_SetAttrString(obj, attrname, val);
	Py_DECREF(val);

	return result != -1;
}