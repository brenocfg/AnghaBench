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
 int /*<<< orphan*/ * PyObject_GetAttrString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PyString_AsString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_None ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 
 char* pstrdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
get_string_attr(PyObject *obj, char *attrname, char **str)
{
	PyObject   *val;

	val = PyObject_GetAttrString(obj, attrname);
	if (val != NULL && val != Py_None)
	{
		*str = pstrdup(PyString_AsString(val));
	}
	Py_XDECREF(val);
}