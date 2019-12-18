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
struct TYPE_6__ {int /*<<< orphan*/  flags; void* data; int /*<<< orphan*/ * base; } ;
struct TYPE_5__ {scalar_t__ len; void* buf; } ;
typedef  scalar_t__ Py_ssize_t ;
typedef  TYPE_1__ Py_buffer ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_2__ PyArrayObject_fields ;
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 int DEPRECATE (char*) ; 
 int /*<<< orphan*/  NPY_ARRAY_CARRAY ; 
 int NPY_ARRAY_OWNDATA ; 
 int NPY_ARRAY_UPDATEIFCOPY ; 
 int NPY_ARRAY_WRITEABLE ; 
 int NPY_ARRAY_WRITEBACKIFCOPY ; 
 scalar_t__ PyArray_BASE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_CLEARFLAGS (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  PyArray_DATA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_ENABLEFLAGS (int /*<<< orphan*/ *,int) ; 
 int PyArray_FLAGS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_ISONESEGMENT (int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_NBYTES (int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_SetBaseObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_XDECREF (int /*<<< orphan*/ *) ; 
 int PyBUF_SIMPLE ; 
 int PyBUF_WRITABLE ; 
 int /*<<< orphan*/  PyBuffer_Release (TYPE_1__*) ; 
 int /*<<< orphan*/  PyDataMem_FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyErr_Clear () ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_AttributeError ; 
 scalar_t__ PyObject_AsReadBuffer (int /*<<< orphan*/ *,void const**,scalar_t__*) ; 
 scalar_t__ PyObject_AsWriteBuffer (int /*<<< orphan*/ *,void**,scalar_t__*) ; 
 scalar_t__ PyObject_GetBuffer (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  Py_DECREF (scalar_t__) ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _dealloc_cached_buffer_info (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
array_data_set(PyArrayObject *self, PyObject *op)
{
    void *buf;
    Py_ssize_t buf_len;
    int writeable=1;
#if defined(NPY_PY3K)
    Py_buffer view;
#endif

    /* 2016-19-02, 1.12 */
    int ret = DEPRECATE("Assigning the 'data' attribute is an "
                        "inherently unsafe operation and will "
                        "be removed in the future.");
    if (ret < 0) {
        return -1;
    }

    if (op == NULL) {
        PyErr_SetString(PyExc_AttributeError,
                "Cannot delete array data");
        return -1;
    }
#if defined(NPY_PY3K)
    if (PyObject_GetBuffer(op, &view, PyBUF_WRITABLE|PyBUF_SIMPLE) < 0) {
        writeable = 0;
        PyErr_Clear();
        if (PyObject_GetBuffer(op, &view, PyBUF_SIMPLE) < 0) {
            return -1;
        }
    }
    buf = view.buf;
    buf_len = view.len;
    /*
     * In Python 3 both of the deprecated functions PyObject_AsWriteBuffer and
     * PyObject_AsReadBuffer that this code replaces release the buffer. It is
     * up to the object that supplies the buffer to guarantee that the buffer
     * sticks around after the release.
     */
    PyBuffer_Release(&view);
    _dealloc_cached_buffer_info(op);
#else
    if (PyObject_AsWriteBuffer(op, &buf, &buf_len) < 0) {
        PyErr_Clear();
        writeable = 0;
        if (PyObject_AsReadBuffer(op, (const void **)&buf, &buf_len) < 0) {
            PyErr_Clear();
            PyErr_SetString(PyExc_AttributeError,
                    "object does not have single-segment buffer interface");
            return -1;
        }
    }
#endif
    if (!PyArray_ISONESEGMENT(self)) {
        PyErr_SetString(PyExc_AttributeError,
                "cannot set single-segment buffer for discontiguous array");
        return -1;
    }
    if (PyArray_NBYTES(self) > buf_len) {
        PyErr_SetString(PyExc_AttributeError, "not enough data for array");
        return -1;
    }
    if (PyArray_FLAGS(self) & NPY_ARRAY_OWNDATA) {
        PyArray_XDECREF(self);
        PyDataMem_FREE(PyArray_DATA(self));
    }
    if (PyArray_BASE(self)) {
        if ((PyArray_FLAGS(self) & NPY_ARRAY_WRITEBACKIFCOPY) ||
            (PyArray_FLAGS(self) & NPY_ARRAY_UPDATEIFCOPY)) {
            PyArray_ENABLEFLAGS((PyArrayObject *)PyArray_BASE(self),
                                                NPY_ARRAY_WRITEABLE);
            PyArray_CLEARFLAGS(self, NPY_ARRAY_WRITEBACKIFCOPY);
            PyArray_CLEARFLAGS(self, NPY_ARRAY_UPDATEIFCOPY);
        }
        Py_DECREF(PyArray_BASE(self));
        ((PyArrayObject_fields *)self)->base = NULL;
    }
    Py_INCREF(op);
    if (PyArray_SetBaseObject(self, op) < 0) {
        return -1;
    }
    ((PyArrayObject_fields *)self)->data = buf;
    ((PyArrayObject_fields *)self)->flags = NPY_ARRAY_CARRAY;
    if (!writeable) {
        PyArray_CLEARFLAGS(self, ~NPY_ARRAY_WRITEABLE);
    }
    return 0;
}