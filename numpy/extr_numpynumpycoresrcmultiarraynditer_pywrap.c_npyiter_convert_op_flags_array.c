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
typedef  int /*<<< orphan*/  npy_uint32 ;
typedef  size_t npy_intp ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int NpyIter_OpFlagsConverter (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ PyBytes_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 int /*<<< orphan*/  PyList_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PySequence_GetItem (int /*<<< orphan*/ *,size_t) ; 
 size_t PySequence_Size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyTuple_Check (int /*<<< orphan*/ *) ; 
 scalar_t__ PyUnicode_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
npyiter_convert_op_flags_array(PyObject *op_flags_in,
                         npy_uint32 *op_flags_array, npy_intp nop)
{
    npy_intp iop;

    if (!PyTuple_Check(op_flags_in) && !PyList_Check(op_flags_in)) {
        PyErr_SetString(PyExc_ValueError,
                "op_flags must be a tuple or array of per-op flag-tuples");
        return 0;
    }

    if (PySequence_Size(op_flags_in) != nop) {
        goto try_single_flags;
    }

    for (iop = 0; iop < nop; ++iop) {
        PyObject *f = PySequence_GetItem(op_flags_in, iop);
        if (f == NULL) {
            return 0;
        }
        /* If the first item is a string, try as one set of flags */
        if (iop == 0 && (PyBytes_Check(f) || PyUnicode_Check(f))) {
            Py_DECREF(f);
            goto try_single_flags;
        }
        if (NpyIter_OpFlagsConverter(f,
                        &op_flags_array[iop]) != 1) {
            Py_DECREF(f);
            return 0;
        }

        Py_DECREF(f);
    }

    return 1;

try_single_flags:
    if (NpyIter_OpFlagsConverter(op_flags_in,
                        &op_flags_array[0]) != 1) {
        return 0;
    }

    for (iop = 1; iop < nop; ++iop) {
        op_flags_array[iop] = op_flags_array[0];
    }

    return 1;
}