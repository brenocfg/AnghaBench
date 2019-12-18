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
typedef  size_t npy_intp ;
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 int /*<<< orphan*/  NPY_INTP ; 
 int /*<<< orphan*/  NPY_QUICKSORT ; 
 int /*<<< orphan*/  PyArray_CanCastSafely (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PyArray_Cast (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t* PyArray_DATA (int /*<<< orphan*/ *) ; 
 int PyArray_NDIM (int /*<<< orphan*/ *) ; 
 size_t* PyArray_SHAPE (int /*<<< orphan*/ *) ; 
 int PyArray_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_Sort (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyArray_TYPE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_Format (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  PyExc_TypeError ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyArrayObject *
partition_prep_kth_array(PyArrayObject * ktharray,
                         PyArrayObject * op,
                         int axis)
{
    const npy_intp * shape = PyArray_SHAPE(op);
    PyArrayObject * kthrvl;
    npy_intp * kth;
    npy_intp nkth, i;

    if (!PyArray_CanCastSafely(PyArray_TYPE(ktharray), NPY_INTP)) {
        PyErr_Format(PyExc_TypeError, "Partition index must be integer");
        return NULL;
    }

    if (PyArray_NDIM(ktharray) > 1) {
        PyErr_Format(PyExc_ValueError, "kth array must have dimension <= 1");
        return NULL;
    }
    kthrvl = (PyArrayObject *)PyArray_Cast(ktharray, NPY_INTP);

    if (kthrvl == NULL)
        return NULL;

    kth = PyArray_DATA(kthrvl);
    nkth = PyArray_SIZE(kthrvl);

    for (i = 0; i < nkth; i++) {
        if (kth[i] < 0) {
            kth[i] += shape[axis];
        }
        if (PyArray_SIZE(op) != 0 &&
                    (kth[i] < 0 || kth[i] >= shape[axis])) {
            PyErr_Format(PyExc_ValueError, "kth(=%zd) out of bounds (%zd)",
                         kth[i], shape[axis]);
            Py_XDECREF(kthrvl);
            return NULL;
        }
    }

    /*
     * sort the array of kths so the partitions will
     * not trample on each other
     */
    if (PyArray_SIZE(kthrvl) > 1) {
        PyArray_Sort(kthrvl, -1, NPY_QUICKSORT);
    }

    return kthrvl;
}