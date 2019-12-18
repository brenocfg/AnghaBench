#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {scalar_t__ ao; } ;
struct TYPE_17__ {scalar_t__ numiter; TYPE_3__** iters; } ;
typedef  TYPE_1__ PyObject ;
typedef  TYPE_1__ PyArrayMultiIterObject ;
typedef  TYPE_3__ PyArrayIterObject ;

/* Variables and functions */
 scalar_t__ NPY_MAXARGS ; 
 int /*<<< orphan*/  PyArrayMultiIter_Type ; 
 scalar_t__ PyArray_Broadcast (TYPE_1__*) ; 
 TYPE_1__* PyArray_FromAny (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_IterNew (TYPE_1__*) ; 
 int /*<<< orphan*/  PyArray_MultiIter_RESET (TYPE_1__*) ; 
 TYPE_1__* PyArray_malloc (int) ; 
 TYPE_1__* PyErr_NoMemory () ; 
 int /*<<< orphan*/  PyObject_Init (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ PyObject_IsInstance (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  Py_DECREF (TYPE_1__*) ; 
 int /*<<< orphan*/  multiiter_wrong_number_of_args () ; 

__attribute__((used)) static PyObject*
multiiter_new_impl(int n_args, PyObject **args)
{
    PyArrayMultiIterObject *multi;
    int i;

    multi = PyArray_malloc(sizeof(PyArrayMultiIterObject));
    if (multi == NULL) {
        return PyErr_NoMemory();
    }
    PyObject_Init((PyObject *)multi, &PyArrayMultiIter_Type);
    multi->numiter = 0;

    for (i = 0; i < n_args; ++i) {
        PyObject *obj = args[i];
        PyObject *arr;
        PyArrayIterObject *it;

        if (PyObject_IsInstance(obj, (PyObject *)&PyArrayMultiIter_Type)) {
            PyArrayMultiIterObject *mit = (PyArrayMultiIterObject *)obj;
            int j;

            if (multi->numiter + mit->numiter > NPY_MAXARGS) {
                multiiter_wrong_number_of_args();
                goto fail;
            }
            for (j = 0; j < mit->numiter; ++j) {
                arr = (PyObject *)mit->iters[j]->ao;
                it = (PyArrayIterObject *)PyArray_IterNew(arr);
                if (it == NULL) {
                    goto fail;
                }
                multi->iters[multi->numiter++] = it;
            }
        }
        else if (multi->numiter < NPY_MAXARGS) {
            arr = PyArray_FromAny(obj, NULL, 0, 0, 0, NULL);
            if (arr == NULL) {
                goto fail;
            }
            it = (PyArrayIterObject *)PyArray_IterNew(arr);
            Py_DECREF(arr);
            if (it == NULL) {
                goto fail;
            }
            multi->iters[multi->numiter++] = it;
        }
        else {
            multiiter_wrong_number_of_args();
            goto fail;
        }
    }

    if (multi->numiter < 0) {
        multiiter_wrong_number_of_args();
        goto fail;
    }
    if (PyArray_Broadcast(multi) < 0) {
        goto fail;
    }
    PyArray_MultiIter_RESET(multi);

    return (PyObject *)multi;

fail:
    Py_DECREF(multi);

    return NULL;
}