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
typedef  scalar_t__ npy_bool ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyArray_Descr ;
typedef  int /*<<< orphan*/  PyArrayObject_fields ;
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 int /*<<< orphan*/  NPY_ANYORDER ; 
 int NPY_MAXDIMS ; 
 scalar_t__ PyArray_CopyInto (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_DATA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyArray_DESCR (int /*<<< orphan*/ *) ; 
 int* PyArray_DIMS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_FLAGS (int /*<<< orphan*/ *) ; 
 int PyArray_NDIM (int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_NewFromDescr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_NewLikeArray (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int* PyArray_STRIDES (int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_SetBaseObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_SetWritebackIfCopyBase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_Type ; 
 int /*<<< orphan*/  PyErr_Format (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyArrayObject *
conform_reduce_result(int ndim, const npy_bool *axis_flags,
                      PyArrayObject *out, int keepdims, const char *funcname,
                      int need_copy)
{
    npy_intp strides[NPY_MAXDIMS], shape[NPY_MAXDIMS];
    npy_intp *strides_out = PyArray_STRIDES(out);
    npy_intp *shape_out = PyArray_DIMS(out);
    int idim, idim_out, ndim_out = PyArray_NDIM(out);
    PyArray_Descr *dtype;
    PyArrayObject_fields *ret;

    /*
     * If the 'keepdims' parameter is true, do a simpler validation and
     * return a new reference to 'out'.
     */
    if (keepdims) {
        if (PyArray_NDIM(out) != ndim) {
            PyErr_Format(PyExc_ValueError,
                    "output parameter for reduction operation %s "
                    "has the wrong number of dimensions (must match "
                    "the operand's when keepdims=True)", funcname);
            return NULL;
        }

        for (idim = 0; idim < ndim; ++idim) {
            if (axis_flags[idim]) {
                if (shape_out[idim] != 1) {
                    PyErr_Format(PyExc_ValueError,
                            "output parameter for reduction operation %s "
                            "has a reduction dimension not equal to one "
                            "(required when keepdims=True)", funcname);
                    return NULL;
                }
            }
        }

        Py_INCREF(out);
        return out;
    }

    /* Construct the strides and shape */
    idim_out = 0;
    for (idim = 0; idim < ndim; ++idim) {
        if (axis_flags[idim]) {
            strides[idim] = 0;
            shape[idim] = 1;
        }
        else {
            if (idim_out >= ndim_out) {
                PyErr_Format(PyExc_ValueError,
                        "output parameter for reduction operation %s "
                        "does not have enough dimensions", funcname);
                return NULL;
            }
            strides[idim] = strides_out[idim_out];
            shape[idim] = shape_out[idim_out];
            ++idim_out;
        }
    }

    if (idim_out != ndim_out) {
        PyErr_Format(PyExc_ValueError,
                "output parameter for reduction operation %s "
                "has too many dimensions", funcname);
        return NULL;
    }

    /* Allocate the view */
    dtype = PyArray_DESCR(out);
    Py_INCREF(dtype);

    /* TODO: use PyArray_NewFromDescrAndBase here once multiarray and umath
     *       are merged
     */
    ret = (PyArrayObject_fields *)PyArray_NewFromDescr(
            &PyArray_Type, dtype,
            ndim, shape, strides, PyArray_DATA(out),
            PyArray_FLAGS(out), NULL);
    if (ret == NULL) {
        return NULL;
    }

    Py_INCREF(out);
    if (PyArray_SetBaseObject((PyArrayObject *)ret, (PyObject *)out) < 0) {
        Py_DECREF(ret);
        return NULL;
    }

    if (need_copy) {
        PyArrayObject *ret_copy;

        ret_copy = (PyArrayObject *)PyArray_NewLikeArray(
            (PyArrayObject *)ret, NPY_ANYORDER, NULL, 0);
        if (ret_copy == NULL) {
            Py_DECREF(ret);
            return NULL;
        }

        if (PyArray_CopyInto(ret_copy, (PyArrayObject *)ret) != 0) {
            Py_DECREF(ret);
            Py_DECREF(ret_copy);
            return NULL;
        }

        if (PyArray_SetWritebackIfCopyBase(ret_copy, (PyArrayObject *)ret) < 0) {
            Py_DECREF(ret);
            Py_DECREF(ret_copy);
            return NULL;
        }

        return ret_copy;
    }
    else {
        return (PyArrayObject *)ret;
    }
}