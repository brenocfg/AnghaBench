#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int contiguous; int nd_m1; int* factors; int* dims_m1; int* strides; int* backstrides; int** bounds; int** limits; int* limits_sizes; int /*<<< orphan*/ * translate; int /*<<< orphan*/  size; int /*<<< orphan*/ * ao; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyArrayObject ;
typedef  TYPE_1__ PyArrayIterObject ;

/* Variables and functions */
 int /*<<< orphan*/  NPY_ARRAY_C_CONTIGUOUS ; 
 int* PyArray_DIMS (int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_ISCONTIGUOUS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_ITER_RESET (TYPE_1__*) ; 
 int PyArray_NDIM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_SIZE (int /*<<< orphan*/ *) ; 
 int* PyArray_STRIDES (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_UpdateFlags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_ptr_simple ; 

__attribute__((used)) static PyObject *
array_iter_base_init(PyArrayIterObject *it, PyArrayObject *ao)
{
    int nd, i;

    nd = PyArray_NDIM(ao);
    PyArray_UpdateFlags(ao, NPY_ARRAY_C_CONTIGUOUS);
    if (PyArray_ISCONTIGUOUS(ao)) {
        it->contiguous = 1;
    }
    else {
        it->contiguous = 0;
    }
    Py_INCREF(ao);
    it->ao = ao;
    it->size = PyArray_SIZE(ao);
    it->nd_m1 = nd - 1;
    if (nd != 0) {
        it->factors[nd-1] = 1;
    }
    for (i = 0; i < nd; i++) {
        it->dims_m1[i] = PyArray_DIMS(ao)[i] - 1;
        it->strides[i] = PyArray_STRIDES(ao)[i];
        it->backstrides[i] = it->strides[i] * it->dims_m1[i];
        if (i > 0) {
            it->factors[nd-i-1] = it->factors[nd-i] * PyArray_DIMS(ao)[nd-i];
        }
        it->bounds[i][0] = 0;
        it->bounds[i][1] = PyArray_DIMS(ao)[i] - 1;
        it->limits[i][0] = 0;
        it->limits[i][1] = PyArray_DIMS(ao)[i] - 1;
        it->limits_sizes[i] = it->limits[i][1] - it->limits[i][0] + 1;
    }

    it->translate = &get_ptr_simple;
    PyArray_ITER_RESET(it);

    return (PyObject *)it;
}