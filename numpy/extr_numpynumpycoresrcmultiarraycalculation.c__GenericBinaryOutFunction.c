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
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 int /*<<< orphan*/ * PyObject_Call (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyObject_CallFunction (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_BuildValue (char*,char*,char*,...) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyObject *
_GenericBinaryOutFunction(PyArrayObject *m1, PyObject *m2, PyArrayObject *out,
                          PyObject *op)
{
    if (out == NULL) {
        return PyObject_CallFunction(op, "OO", m1, m2);
    }
    else {
        PyObject *args, *ret;
        static PyObject *kw = NULL;

        if (kw == NULL) {
            kw = Py_BuildValue("{s:s}", "casting", "unsafe");
            if (kw == NULL) {
                return NULL;
            }
        }

        args = Py_BuildValue("OOO", m1, m2, out);
        if (args == NULL) {
            return NULL;
        }

        ret = PyObject_Call(op, args, kw);

        Py_DECREF(args);

        return ret;
    }
}