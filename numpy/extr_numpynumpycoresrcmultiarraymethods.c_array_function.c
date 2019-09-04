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
 int /*<<< orphan*/  PyArg_ParseTupleAndKeywords (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char**,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * PySequence_Fast (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * array_function_method_impl (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyObject *
array_function(PyArrayObject *self, PyObject *c_args, PyObject *c_kwds)
{
    PyObject *func, *types, *args, *kwargs, *result;
    static char *kwlist[] = {"func", "types", "args", "kwargs", NULL};

    if (!PyArg_ParseTupleAndKeywords(
            c_args, c_kwds, "OOOO:__array_function__", kwlist,
            &func, &types, &args, &kwargs)) {
        return NULL;
    }

    types = PySequence_Fast(
        types,
        "types argument to ndarray.__array_function__ must be iterable");
    if (types == NULL) {
        return NULL;
    }

    result = array_function_method_impl(func, types, args, kwargs);
    Py_DECREF(types);
    return result;
}