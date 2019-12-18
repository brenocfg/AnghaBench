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
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyArray_Descr ;

/* Variables and functions */
 int PyArray_DescrConverter2 (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  PyErr_Clear () ; 
 int /*<<< orphan*/  PyList_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PySequence_GetItem (int /*<<< orphan*/ *,size_t) ; 
 size_t PySequence_Size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyTuple_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_XINCREF (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
npyiter_convert_dtypes(PyObject *op_dtypes_in,
                        PyArray_Descr **op_dtypes,
                        npy_intp nop)
{
    npy_intp iop;

    /*
     * If the input isn't a tuple of dtypes, try converting it as-is
     * to a dtype, and replicating to all operands.
     */
    if ((!PyTuple_Check(op_dtypes_in) && !PyList_Check(op_dtypes_in)) ||
                                    PySequence_Size(op_dtypes_in) != nop) {
        goto try_single_dtype;
    }

    for (iop = 0; iop < nop; ++iop) {
        PyObject *dtype = PySequence_GetItem(op_dtypes_in, iop);
        if (dtype == NULL) {
            npy_intp i;
            for (i = 0; i < iop; ++i ) {
                Py_XDECREF(op_dtypes[i]);
            }
            return 0;
        }

        /* Try converting the object to a descr */
        if (PyArray_DescrConverter2(dtype, &op_dtypes[iop]) != 1) {
            npy_intp i;
            for (i = 0; i < iop; ++i ) {
                Py_XDECREF(op_dtypes[i]);
            }
            Py_DECREF(dtype);
            PyErr_Clear();
            goto try_single_dtype;
        }

        Py_DECREF(dtype);
    }

    return 1;

try_single_dtype:
    if (PyArray_DescrConverter2(op_dtypes_in, &op_dtypes[0]) == 1) {
        for (iop = 1; iop < nop; ++iop) {
            op_dtypes[iop] = op_dtypes[0];
            Py_XINCREF(op_dtypes[iop]);
        }
        return 1;
    }

    return 0;
}