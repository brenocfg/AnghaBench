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
typedef  scalar_t__ npy_intp ;
typedef  int /*<<< orphan*/  npy_bool ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyArray_Descr ;
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 int /*<<< orphan*/  NPY_ARRAY_CARRAY ; 
 int /*<<< orphan*/  NPY_BEGIN_THREADS_DEF ; 
 int /*<<< orphan*/  NPY_BEGIN_THREADS_THRESHOLDED (scalar_t__) ; 
 int /*<<< orphan*/  NPY_BOOL ; 
 int /*<<< orphan*/  NPY_END_THREADS ; 
 int /*<<< orphan*/  NPY_INTP ; 
 int NPY_MAXDIMS ; 
 scalar_t__ PyArray_DATA (int /*<<< orphan*/ *) ; 
 scalar_t__* PyArray_DIMS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyArray_DescrFromType (int /*<<< orphan*/ ) ; 
 scalar_t__ PyArray_FromAny (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int PyArray_NDIM (int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_NewFromDescr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_Type ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 
 scalar_t__ count_boolean_trues (int,char*,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static int
_nonzero_indices(PyObject *myBool, PyArrayObject **arrays)
{
    PyArray_Descr *typecode;
    PyArrayObject *ba = NULL, *new = NULL;
    int nd, j;
    npy_intp size, i, count;
    npy_bool *ptr;
    npy_intp coords[NPY_MAXDIMS], dims_m1[NPY_MAXDIMS];
    npy_intp *dptr[NPY_MAXDIMS];
    static npy_intp one = 1;
    NPY_BEGIN_THREADS_DEF;

    typecode=PyArray_DescrFromType(NPY_BOOL);
    ba = (PyArrayObject *)PyArray_FromAny(myBool, typecode, 0, 0,
                                          NPY_ARRAY_CARRAY, NULL);
    if (ba == NULL) {
        return -1;
    }
    nd = PyArray_NDIM(ba);

    for (j = 0; j < nd; j++) {
        arrays[j] = NULL;
    }
    size = PyArray_SIZE(ba);
    ptr = (npy_bool *)PyArray_DATA(ba);

    /*
     * pre-determine how many nonzero entries there are,
     * ignore dimensionality of input as its a CARRAY
     */
    count = count_boolean_trues(1, (char*)ptr, &size, &one);

    /* create count-sized index arrays for each dimension */
    for (j = 0; j < nd; j++) {
        new = (PyArrayObject *)PyArray_NewFromDescr(
            &PyArray_Type, PyArray_DescrFromType(NPY_INTP),
            1, &count, NULL, NULL,
            0, NULL);
        if (new == NULL) {
            goto fail;
        }
        arrays[j] = new;

        dptr[j] = (npy_intp *)PyArray_DATA(new);
        coords[j] = 0;
        dims_m1[j] = PyArray_DIMS(ba)[j]-1;
    }
    if (count == 0) {
        goto finish;
    }

    /*
     * Loop through the Boolean array  and copy coordinates
     * for non-zero entries
     */
    NPY_BEGIN_THREADS_THRESHOLDED(size);
    for (i = 0; i < size; i++) {
        if (*(ptr++)) {
            for (j = 0; j < nd; j++) {
                *(dptr[j]++) = coords[j];
            }
        }
        /* Borrowed from ITER_NEXT macro */
        for (j = nd - 1; j >= 0; j--) {
            if (coords[j] < dims_m1[j]) {
                coords[j]++;
                break;
            }
            else {
                coords[j] = 0;
            }
        }
    }
    NPY_END_THREADS;

 finish:
    Py_DECREF(ba);
    return nd;

 fail:
    for (j = 0; j < nd; j++) {
        Py_XDECREF(arrays[j]);
    }
    Py_XDECREF(ba);
    return -1;
}