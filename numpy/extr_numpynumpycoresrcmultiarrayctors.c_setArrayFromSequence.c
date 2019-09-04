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
typedef  int Py_ssize_t ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 char* PyArray_BYTES (int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_CheckExact (int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_CopyInto (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int PyArray_DIM (int /*<<< orphan*/ *,int) ; 
 int* PyArray_DIMS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyArray_EnsureArray (int /*<<< orphan*/ *) ; 
 int PyArray_NDIM (int /*<<< orphan*/ *) ; 
 int PyArray_SETITEM (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int* PyArray_STRIDES (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_Format (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 int /*<<< orphan*/ * PySequence_Fast (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * PySequence_Fast_GET_ITEM (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * PySequence_GetItem (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int PySequence_Length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 
 scalar_t__ array_item_asarray (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
setArrayFromSequence(PyArrayObject *a, PyObject *s,
                        int dim, PyArrayObject * dst)
{
    Py_ssize_t i, slen;
    int res = -1;

    /* first recursion, view equal destination */
    if (dst == NULL)
        dst = a;

    /*
     * This code is to ensure that the sequence access below will
     * return a lower-dimensional sequence.
     */

    /* INCREF on entry DECREF on exit */
    Py_INCREF(s);

    if (PyArray_Check(s)) {
        if (!(PyArray_CheckExact(s))) {
            /*
             * make sure a base-class array is used so that the dimensionality
             * reduction assumption is correct.
             */
            /* This will DECREF(s) if replaced */
            s = PyArray_EnsureArray(s);
            if (s == NULL) {
                goto fail;
            }
        }

        /* dst points to correct array subsection */
        if (PyArray_CopyInto(dst, (PyArrayObject *)s) < 0) {
            goto fail;
        }

        Py_DECREF(s);
        return 0;
    }

    if (dim > PyArray_NDIM(a)) {
        PyErr_Format(PyExc_ValueError,
                 "setArrayFromSequence: sequence/array dimensions mismatch.");
        goto fail;
    }

    slen = PySequence_Length(s);
    if (slen < 0) {
        goto fail;
    }
    /*
     * Either the dimensions match, or the sequence has length 1 and can
     * be broadcast to the destination.
     */
    if (slen != PyArray_DIMS(a)[dim] && slen != 1) {
        PyErr_Format(PyExc_ValueError,
                 "cannot copy sequence with size %d to array axis "
                 "with dimension %d", (int)slen, (int)PyArray_DIMS(a)[dim]);
        goto fail;
    }

    /* Broadcast the one element from the sequence to all the outputs */
    if (slen == 1) {
        PyObject *o;
        npy_intp alen = PyArray_DIM(a, dim);

        o = PySequence_GetItem(s, 0);
        if (o == NULL) {
            goto fail;
        }

        for (i = 0; i < alen; i++) {
            if ((PyArray_NDIM(a) - dim) > 1) {
                PyArrayObject * tmp =
                    (PyArrayObject *)array_item_asarray(dst, i);
                if (tmp == NULL) {
                    goto fail;
                }

                res = setArrayFromSequence(a, o, dim+1, tmp);
                Py_DECREF(tmp);
            }
            else {
                char * b = (PyArray_BYTES(dst) + i * PyArray_STRIDES(dst)[0]);
                res = PyArray_SETITEM(dst, b, o);
            }
            if (res < 0) {
                Py_DECREF(o);
                goto fail;
            }
        }
        Py_DECREF(o);
    }
    /* Copy element by element */
    else {
        PyObject * seq;
        seq = PySequence_Fast(s, "Could not convert object to sequence");
        if (seq == NULL) {
            goto fail;
        }
        for (i = 0; i < slen; i++) {
            PyObject * o = PySequence_Fast_GET_ITEM(seq, i);
            if ((PyArray_NDIM(a) - dim) > 1) {
                PyArrayObject * tmp =
                    (PyArrayObject *)array_item_asarray(dst, i);
                if (tmp == NULL) {
                    Py_DECREF(seq);
                    goto fail;
                }

                res = setArrayFromSequence(a, o, dim+1, tmp);
                Py_DECREF(tmp);
            }
            else {
                char * b = (PyArray_BYTES(dst) + i * PyArray_STRIDES(dst)[0]);
                res = PyArray_SETITEM(dst, b, o);
            }
            if (res < 0) {
                Py_DECREF(seq);
                goto fail;
            }
        }
        Py_DECREF(seq);
    }

    Py_DECREF(s);
    return 0;

 fail:
    Py_DECREF(s);
    return res;
}