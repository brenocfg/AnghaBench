#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int (* type_resolver ) (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ;} ;
typedef  TYPE_1__ PyUFuncObject ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyArray_Descr ;
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 int /*<<< orphan*/  NPY_UNSAFE_CASTING ; 
 int /*<<< orphan*/  PyArray_EquivTypes (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_Format (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  PyExc_RuntimeError ; 
 int /*<<< orphan*/ * PyTuple_Pack (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_None ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 char* ufunc_get_name_cstr (TYPE_1__*) ; 

__attribute__((used)) static int
reduce_type_resolver(PyUFuncObject *ufunc, PyArrayObject *arr,
                        PyArray_Descr *odtype, PyArray_Descr **out_dtype)
{
    int i, retcode;
    PyArrayObject *op[3] = {arr, arr, NULL};
    PyArray_Descr *dtypes[3] = {NULL, NULL, NULL};
    const char *ufunc_name = ufunc_get_name_cstr(ufunc);
    PyObject *type_tup = NULL;

    *out_dtype = NULL;

    /*
     * If odtype is specified, make a type tuple for the type
     * resolution.
     */
    if (odtype != NULL) {
        type_tup = PyTuple_Pack(3, odtype, odtype, Py_None);
        if (type_tup == NULL) {
            return -1;
        }
    }

    /* Use the type resolution function to find our loop */
    retcode = ufunc->type_resolver(
                        ufunc, NPY_UNSAFE_CASTING,
                        op, type_tup, dtypes);
    Py_DECREF(type_tup);
    if (retcode == -1) {
        return -1;
    }
    else if (retcode == -2) {
        PyErr_Format(PyExc_RuntimeError,
                "type resolution returned NotImplemented to "
                "reduce ufunc %s", ufunc_name);
        return -1;
    }

    /*
     * The first two type should be equivalent. Because of how
     * reduce has historically behaved in NumPy, the return type
     * could be different, and it is the return type on which the
     * reduction occurs.
     */
    if (!PyArray_EquivTypes(dtypes[0], dtypes[1])) {
        for (i = 0; i < 3; ++i) {
            Py_DECREF(dtypes[i]);
        }
        PyErr_Format(PyExc_RuntimeError,
                "could not find a type resolution appropriate for "
                "reduce ufunc %s", ufunc_name);
        return -1;
    }

    Py_DECREF(dtypes[0]);
    Py_DECREF(dtypes[1]);
    *out_dtype = dtypes[2];

    return 0;
}