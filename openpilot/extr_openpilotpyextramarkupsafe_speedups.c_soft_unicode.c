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
 int /*<<< orphan*/ * PyObject_Unicode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyUnicode_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyObject*
soft_unicode(PyObject *self, PyObject *s)
{
	if (!PyUnicode_Check(s))
#if PY_MAJOR_VERSION < 3
		return PyObject_Unicode(s);
#else
		return PyObject_Str(s);
#endif
	Py_INCREF(s);
	return s;
}