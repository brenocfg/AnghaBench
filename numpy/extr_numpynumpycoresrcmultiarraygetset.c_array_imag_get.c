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
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 int /*<<< orphan*/  NPY_ARRAY_WRITEABLE ; 
 int /*<<< orphan*/  PyArray_CLEARFLAGS (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyArray_DESCR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_DIMS (int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_ISCOMPLEX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_ISFORTRAN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_NDIM (int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_NewFromDescr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Py_TYPE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * _get_part (int /*<<< orphan*/ *,int) ; 
 scalar_t__ _zerofill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyObject *
array_imag_get(PyArrayObject *self)
{
    PyArrayObject *ret;

    if (PyArray_ISCOMPLEX(self)) {
        ret = _get_part(self, 1);
    }
    else {
        Py_INCREF(PyArray_DESCR(self));
        ret = (PyArrayObject *)PyArray_NewFromDescr(Py_TYPE(self),
                                                    PyArray_DESCR(self),
                                                    PyArray_NDIM(self),
                                                    PyArray_DIMS(self),
                                                    NULL, NULL,
                                                    PyArray_ISFORTRAN(self),
                                                    (PyObject *)self);
        if (ret == NULL) {
            return NULL;
        }
        if (_zerofill(ret) < 0) {
            return NULL;
        }
        PyArray_CLEARFLAGS(ret, NPY_ARRAY_WRITEABLE);
    }
    return (PyObject *) ret;
}