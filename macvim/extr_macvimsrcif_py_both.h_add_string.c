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
 scalar_t__ PyList_Append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyString_FromString (char*) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
add_string(PyObject *list, char *s)
{
    PyObject	*string;

    if (!(string = PyString_FromString(s)))
	return -1;

    if (PyList_Append(list, string))
    {
	Py_DECREF(string);
	return -1;
    }

    Py_DECREF(string);
    return 0;
}