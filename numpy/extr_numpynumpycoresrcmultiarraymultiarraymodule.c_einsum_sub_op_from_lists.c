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
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 int /*<<< orphan*/  NPY_ARRAY_ENSUREARRAY ; 
 size_t NPY_MAXARGS ; 
 scalar_t__ PyArray_FROM_OF (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 int /*<<< orphan*/ * PyTuple_GET_ITEM (int /*<<< orphan*/ *,int) ; 
 int PyTuple_Size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 
 int einsum_list_to_subscripts (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int
einsum_sub_op_from_lists(PyObject *args,
                char *subscripts, int subsize, PyArrayObject **op)
{
    int subindex = 0;
    npy_intp i, nop;

    nop = PyTuple_Size(args)/2;

    if (nop == 0) {
        PyErr_SetString(PyExc_ValueError, "must provide at least an "
                        "operand and a subscripts list to einsum");
        return -1;
    }
    else if (nop >= NPY_MAXARGS) {
        PyErr_SetString(PyExc_ValueError, "too many operands");
        return -1;
    }

    /* Set the operands to NULL */
    for (i = 0; i < nop; ++i) {
        op[i] = NULL;
    }

    /* Get the operands and build the subscript string */
    for (i = 0; i < nop; ++i) {
        PyObject *obj = PyTuple_GET_ITEM(args, 2*i);
        int n;

        /* Comma between the subscripts for each operand */
        if (i != 0) {
            subscripts[subindex++] = ',';
            if (subindex >= subsize) {
                PyErr_SetString(PyExc_ValueError,
                        "subscripts list is too long");
                goto fail;
            }
        }

        op[i] = (PyArrayObject *)PyArray_FROM_OF(obj, NPY_ARRAY_ENSUREARRAY);
        if (op[i] == NULL) {
            goto fail;
        }

        obj = PyTuple_GET_ITEM(args, 2*i+1);
        n = einsum_list_to_subscripts(obj, subscripts+subindex,
                                      subsize-subindex);
        if (n < 0) {
            goto fail;
        }
        subindex += n;
    }

    /* Add the '->' to the string if provided */
    if (PyTuple_Size(args) == 2*nop+1) {
        PyObject *obj;
        int n;

        if (subindex + 2 >= subsize) {
            PyErr_SetString(PyExc_ValueError,
                    "subscripts list is too long");
            goto fail;
        }
        subscripts[subindex++] = '-';
        subscripts[subindex++] = '>';

        obj = PyTuple_GET_ITEM(args, 2*nop);
        n = einsum_list_to_subscripts(obj, subscripts+subindex,
                                      subsize-subindex);
        if (n < 0) {
            goto fail;
        }
        subindex += n;
    }

    /* NULL-terminate the subscripts string */
    subscripts[subindex] = '\0';

    return nop;

fail:
    for (i = 0; i < nop; ++i) {
        Py_XDECREF(op[i]);
        op[i] = NULL;
    }

    return -1;
}