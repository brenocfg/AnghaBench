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
typedef  int npy_uint32 ;
typedef  int npy_intp ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 int NPY_ARRAY_WRITEBACKIFCOPY ; 
 int NPY_ITER_ALLOCATE ; 
 int NPY_ITER_READONLY ; 
 int NPY_ITER_READWRITE ; 
 int NPY_ITER_WRITEONLY ; 
 int NPY_MAXARGS ; 
 scalar_t__ PyArray_FROM_OF (int /*<<< orphan*/ *,int) ; 
 scalar_t__ PyErr_ExceptionMatches (int /*<<< orphan*/ ) ; 
 scalar_t__ PyErr_Occurred () ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_TypeError ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 scalar_t__ PyList_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PySequence_GetItem (int /*<<< orphan*/ *,int) ; 
 int PySequence_Size (int /*<<< orphan*/ *) ; 
 scalar_t__ PyTuple_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_None ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 
 int npyiter_convert_op_flags_array (int /*<<< orphan*/ *,int*,int) ; 

__attribute__((used)) static int
npyiter_convert_ops(PyObject *op_in, PyObject *op_flags_in,
                    PyArrayObject **op, npy_uint32 *op_flags,
                    int *nop_out)
{
    int iop, nop;

    /* nop and op */
    if (PyTuple_Check(op_in) || PyList_Check(op_in)) {
        nop = PySequence_Size(op_in);
        if (nop == 0) {
            PyErr_SetString(PyExc_ValueError,
                    "Must provide at least one operand");
            return 0;
        }
        if (nop > NPY_MAXARGS) {
            PyErr_SetString(PyExc_ValueError, "Too many operands");
            return 0;
        }

        for (iop = 0; iop < nop; ++iop) {
            PyObject *item = PySequence_GetItem(op_in, iop);
            if (item == NULL) {
                npy_intp i;
                for (i = 0; i < iop; ++i) {
                    Py_XDECREF(op[i]);
                }
                return 0;
            }
            else if (item == Py_None) {
                Py_DECREF(item);
                item = NULL;
            }
            /* This is converted to an array after op flags are retrieved */
            op[iop] = (PyArrayObject *)item;
        }
    }
    else {
        nop = 1;
        /* Is converted to an array after op flags are retrieved */
        Py_INCREF(op_in);
        op[0] = (PyArrayObject *)op_in;
    }

    *nop_out = nop;

    /* op_flags */
    if (op_flags_in == NULL || op_flags_in == Py_None) {
        for (iop = 0; iop < nop; ++iop) {
            /*
             * By default, make NULL operands writeonly and flagged for
             * allocation, and everything else readonly.  To write
             * to a provided operand, you must specify the write flag manually.
             */
            if (op[iop] == NULL) {
                op_flags[iop] = NPY_ITER_WRITEONLY | NPY_ITER_ALLOCATE;
            }
            else {
                op_flags[iop] = NPY_ITER_READONLY;
            }
        }
    }
    else if (npyiter_convert_op_flags_array(op_flags_in,
                                      op_flags, nop) != 1) {
        for (iop = 0; iop < nop; ++iop) {
            Py_XDECREF(op[iop]);
        }
        *nop_out = 0;
        return 0;
    }

    /* Now that we have the flags - convert all the ops to arrays */
    for (iop = 0; iop < nop; ++iop) {
        if (op[iop] != NULL) {
            PyArrayObject *ao;
            int fromanyflags = 0;

            if (op_flags[iop]&(NPY_ITER_READWRITE|NPY_ITER_WRITEONLY)) {
                fromanyflags |= NPY_ARRAY_WRITEBACKIFCOPY;
            }
            ao = (PyArrayObject *)PyArray_FROM_OF((PyObject *)op[iop],
                                                  fromanyflags);
            if (ao == NULL) {
                if (PyErr_Occurred() &&
                            PyErr_ExceptionMatches(PyExc_TypeError)) {
                    PyErr_SetString(PyExc_TypeError,
                            "Iterator operand is flagged as writeable, "
                            "but is an object which cannot be written "
                            "back to via WRITEBACKIFCOPY");
                }
                for (iop = 0; iop < nop; ++iop) {
                    Py_DECREF(op[iop]);
                }
                *nop_out = 0;
                return 0;
            }
            Py_DECREF(op[iop]);
            op[iop] = ao;
        }
    }

    return 1;
}