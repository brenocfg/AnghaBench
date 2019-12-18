#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int ndim; void** shape; void** strides; int /*<<< orphan*/ * format; } ;
typedef  TYPE_1__ _buffer_info_t ;
struct TYPE_6__ {int readonly; int ndim; void** shape; int /*<<< orphan*/ * obj; void** strides; void* itemsize; int /*<<< orphan*/ * format; int /*<<< orphan*/  len; int /*<<< orphan*/ * internal; int /*<<< orphan*/ * suboffsets; int /*<<< orphan*/  buf; } ;
typedef  void* Py_ssize_t ;
typedef  TYPE_2__ Py_buffer ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 int /*<<< orphan*/  NPY_ARRAY_C_CONTIGUOUS ; 
 int /*<<< orphan*/  NPY_ARRAY_F_CONTIGUOUS ; 
 int /*<<< orphan*/  NPY_ARRAY_WARN_ON_WRITE ; 
 scalar_t__ PyArray_CHKFLAGS (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyArray_DATA (int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_FailUnlessWriteable (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PyArray_ISONESEGMENT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_ISWRITEABLE (int /*<<< orphan*/ *) ; 
 void* PyArray_ITEMSIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_NBYTES (int /*<<< orphan*/ *) ; 
 int PyBUF_ANY_CONTIGUOUS ; 
 int PyBUF_C_CONTIGUOUS ; 
 int PyBUF_FORMAT ; 
 int PyBUF_F_CONTIGUOUS ; 
 int PyBUF_ND ; 
 int PyBUF_STRIDES ; 
 int PyBUF_WRITEABLE ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 
 TYPE_1__* _buffer_get_info (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
array_getbuffer(PyObject *obj, Py_buffer *view, int flags)
{
    PyArrayObject *self;
    _buffer_info_t *info = NULL;

    self = (PyArrayObject*)obj;

    /* Check whether we can provide the wanted properties */
    if ((flags & PyBUF_C_CONTIGUOUS) == PyBUF_C_CONTIGUOUS &&
            !PyArray_CHKFLAGS(self, NPY_ARRAY_C_CONTIGUOUS)) {
        PyErr_SetString(PyExc_ValueError, "ndarray is not C-contiguous");
        goto fail;
    }
    if ((flags & PyBUF_F_CONTIGUOUS) == PyBUF_F_CONTIGUOUS &&
            !PyArray_CHKFLAGS(self, NPY_ARRAY_F_CONTIGUOUS)) {
        PyErr_SetString(PyExc_ValueError, "ndarray is not Fortran contiguous");
        goto fail;
    }
    if ((flags & PyBUF_ANY_CONTIGUOUS) == PyBUF_ANY_CONTIGUOUS
            && !PyArray_ISONESEGMENT(self)) {
        PyErr_SetString(PyExc_ValueError, "ndarray is not contiguous");
        goto fail;
    }
    if ((flags & PyBUF_STRIDES) != PyBUF_STRIDES &&
            !PyArray_CHKFLAGS(self, NPY_ARRAY_C_CONTIGUOUS)) {
        /* Non-strided N-dim buffers must be C-contiguous */
        PyErr_SetString(PyExc_ValueError, "ndarray is not C-contiguous");
        goto fail;
    }
    if ((flags & PyBUF_WRITEABLE) == PyBUF_WRITEABLE) {
        if (PyArray_FailUnlessWriteable(self, "buffer source array") < 0) {
            goto fail;
        }
    }

    if (view == NULL) {
        PyErr_SetString(PyExc_ValueError, "NULL view in getbuffer");
        goto fail;
    }

    /* Fill in information */
    info = _buffer_get_info(obj);
    if (info == NULL) {
        goto fail;
    }

    view->buf = PyArray_DATA(self);
    view->suboffsets = NULL;
    view->itemsize = PyArray_ITEMSIZE(self);
    /*
     * If a read-only buffer is requested on a read-write array, we return a
     * read-write buffer as per buffer protocol.
     * We set a requested buffer to readonly also if the array will be readonly
     * after a deprecation. This jumps the deprecation, but avoiding the
     * warning is not convenient here. A warning is given if a writeable
     * buffer is requested since `PyArray_FailUnlessWriteable` is called above
     * (and clears the `NPY_ARRAY_WARN_ON_WRITE` flag).
     */
    view->readonly = (!PyArray_ISWRITEABLE(self) ||
                      PyArray_CHKFLAGS(self, NPY_ARRAY_WARN_ON_WRITE));
    view->internal = NULL;
    view->len = PyArray_NBYTES(self);
    if ((flags & PyBUF_FORMAT) == PyBUF_FORMAT) {
        view->format = info->format;
    } else {
        view->format = NULL;
    }
    if ((flags & PyBUF_ND) == PyBUF_ND) {
        view->ndim = info->ndim;
        view->shape = info->shape;
    }
    else {
        view->ndim = 0;
        view->shape = NULL;
    }
    if ((flags & PyBUF_STRIDES) == PyBUF_STRIDES) {
        view->strides = info->strides;

#ifdef NPY_RELAXED_STRIDES_CHECKING
        /*
         * If NPY_RELAXED_STRIDES_CHECKING is on, the array may be
         * contiguous, but it won't look that way to Python when it
         * tries to determine contiguity by looking at the strides
         * (since one of the elements may be -1).  In that case, just
         * regenerate strides from shape.
         */
        if (PyArray_CHKFLAGS(self, NPY_ARRAY_C_CONTIGUOUS) &&
                !((flags & PyBUF_F_CONTIGUOUS) == PyBUF_F_CONTIGUOUS)) {
            Py_ssize_t sd = view->itemsize;
            int i;

            for (i = view->ndim-1; i >= 0; --i) {
                view->strides[i] = sd;
                sd *= view->shape[i];
            }
        }
        else if (PyArray_CHKFLAGS(self, NPY_ARRAY_F_CONTIGUOUS)) {
            Py_ssize_t sd = view->itemsize;
            int i;

            for (i = 0; i < view->ndim; ++i) {
                view->strides[i] = sd;
                sd *= view->shape[i];
            }
        }
#endif
    }
    else {
        view->strides = NULL;
    }
    view->obj = (PyObject*)self;

    Py_INCREF(self);
    return 0;

fail:
    return -1;
}