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
typedef  int /*<<< orphan*/  npy_intp ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyArray_StridedUnaryOp ;
typedef  int /*<<< orphan*/  NpyAuxData ;

/* Variables and functions */
 int NPY_FAIL ; 
 int NPY_SUCCEED ; 
 int /*<<< orphan*/ * PyArray_GetStridedNumericCastFn (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int PyErr_WarnEx (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 int /*<<< orphan*/ * PyImport_ImportModule (char*) ; 
 int /*<<< orphan*/ * PyObject_GetAttrString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PyTypeNum_ISBOOL (int) ; 
 scalar_t__ PyTypeNum_ISCOMPLEX (int) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
get_nbo_cast_numeric_transfer_function(int aligned,
                            npy_intp src_stride, npy_intp dst_stride,
                            int src_type_num, int dst_type_num,
                            PyArray_StridedUnaryOp **out_stransfer,
                            NpyAuxData **out_transferdata)
{
    /* Emit a warning if complex imaginary is being cast away */
    if (PyTypeNum_ISCOMPLEX(src_type_num) &&
                    !PyTypeNum_ISCOMPLEX(dst_type_num) &&
                    !PyTypeNum_ISBOOL(dst_type_num)) {
        PyObject *cls = NULL, *obj = NULL;
        int ret;
        obj = PyImport_ImportModule("numpy.core");
        if (obj) {
            cls = PyObject_GetAttrString(obj, "ComplexWarning");
            Py_DECREF(obj);
        }
        ret = PyErr_WarnEx(cls,
                "Casting complex values to real discards "
                "the imaginary part", 1);
        Py_XDECREF(cls);
        if (ret < 0) {
            return NPY_FAIL;
        }
    }

    *out_stransfer = PyArray_GetStridedNumericCastFn(aligned,
                                src_stride, dst_stride,
                                src_type_num, dst_type_num);
    *out_transferdata = NULL;
    if (*out_stransfer == NULL) {
        PyErr_SetString(PyExc_ValueError,
                "unexpected error in GetStridedNumericCastFn");
        return NPY_FAIL;
    }

    return NPY_SUCCEED;
}