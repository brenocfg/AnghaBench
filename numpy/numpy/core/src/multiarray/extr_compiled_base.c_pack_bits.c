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
typedef  int npy_intp ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyArrayObject ;
typedef  int /*<<< orphan*/  PyArrayIterObject ;

/* Variables and functions */
 int /*<<< orphan*/  NPY_BEGIN_THREADS_DEF ; 
 int /*<<< orphan*/  NPY_BEGIN_THREADS_THRESHOLDED (int) ; 
 int /*<<< orphan*/  NPY_END_THREADS ; 
 int NPY_MAXDIMS ; 
 int /*<<< orphan*/  NPY_UBYTE ; 
 scalar_t__ PyArray_CheckAxis (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 char* PyArray_DATA (int /*<<< orphan*/ *) ; 
 int PyArray_DIM (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  PyArray_DescrFromType (int /*<<< orphan*/ ) ; 
 scalar_t__ PyArray_FROM_O (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_ISBOOL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_ISFORTRAN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_ISINTEGER (int /*<<< orphan*/ *) ; 
 int PyArray_ITEMSIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_ITER_DATA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_ITER_NEXT (int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_ITER_NOTDONE (int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_IterAllButAxis (int /*<<< orphan*/ *,int*) ; 
 int PyArray_NDIM (int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_NewFromDescr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_STRIDE (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_TypeError ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_TYPE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pack_inner (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char) ; 

__attribute__((used)) static PyObject *
pack_bits(PyObject *input, int axis, char order)
{
    PyArrayObject *inp;
    PyArrayObject *new = NULL;
    PyArrayObject *out = NULL;
    npy_intp outdims[NPY_MAXDIMS];
    int i;
    PyArrayIterObject *it, *ot;
    NPY_BEGIN_THREADS_DEF;

    inp = (PyArrayObject *)PyArray_FROM_O(input);

    if (inp == NULL) {
        return NULL;
    }
    if (!PyArray_ISBOOL(inp) && !PyArray_ISINTEGER(inp)) {
        PyErr_SetString(PyExc_TypeError,
                "Expected an input array of integer or boolean data type");
        Py_DECREF(inp);
        goto fail;
    }

    new = (PyArrayObject *)PyArray_CheckAxis(inp, &axis, 0);
    Py_DECREF(inp);
    if (new == NULL) {
        return NULL;
    }

    if (PyArray_NDIM(new) == 0) {
        char *optr, *iptr;

        out = (PyArrayObject *)PyArray_NewFromDescr(
                Py_TYPE(new), PyArray_DescrFromType(NPY_UBYTE),
                0, NULL, NULL, NULL,
                0, NULL);
        if (out == NULL) {
            goto fail;
        }
        optr = PyArray_DATA(out);
        iptr = PyArray_DATA(new);
        *optr = 0;
        for (i = 0; i < PyArray_ITEMSIZE(new); i++) {
            if (*iptr != 0) {
                *optr = 1;
                break;
            }
            iptr++;
        }
        goto finish;
    }


    /* Setup output shape */
    for (i = 0; i < PyArray_NDIM(new); i++) {
        outdims[i] = PyArray_DIM(new, i);
    }

    /*
     * Divide axis dimension by 8
     * 8 -> 1, 9 -> 2, 16 -> 2, 17 -> 3 etc..
     */
    outdims[axis] = ((outdims[axis] - 1) >> 3) + 1;

    /* Create output array */
    out = (PyArrayObject *)PyArray_NewFromDescr(
            Py_TYPE(new), PyArray_DescrFromType(NPY_UBYTE),
            PyArray_NDIM(new), outdims, NULL, NULL,
            PyArray_ISFORTRAN(new), NULL);
    if (out == NULL) {
        goto fail;
    }
    /* Setup iterators to iterate over all but given axis */
    it = (PyArrayIterObject *)PyArray_IterAllButAxis((PyObject *)new, &axis);
    ot = (PyArrayIterObject *)PyArray_IterAllButAxis((PyObject *)out, &axis);
    if (it == NULL || ot == NULL) {
        Py_XDECREF(it);
        Py_XDECREF(ot);
        goto fail;
    }

    NPY_BEGIN_THREADS_THRESHOLDED(PyArray_DIM(out, axis));
    while (PyArray_ITER_NOTDONE(it)) {
        pack_inner(PyArray_ITER_DATA(it), PyArray_ITEMSIZE(new),
                   PyArray_DIM(new, axis), PyArray_STRIDE(new, axis),
                   PyArray_ITER_DATA(ot), PyArray_DIM(out, axis),
                   PyArray_STRIDE(out, axis), order);
        PyArray_ITER_NEXT(it);
        PyArray_ITER_NEXT(ot);
    }
    NPY_END_THREADS;

    Py_DECREF(it);
    Py_DECREF(ot);

finish:
    Py_DECREF(new);
    return (PyObject *)out;

fail:
    Py_XDECREF(new);
    Py_XDECREF(out);
    return NULL;
}