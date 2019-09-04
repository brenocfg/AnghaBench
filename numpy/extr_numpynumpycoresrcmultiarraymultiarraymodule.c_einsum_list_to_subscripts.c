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
typedef  scalar_t__ npy_intp ;
typedef  int npy_bool ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 long PyInt_AsLong (int /*<<< orphan*/ *) ; 
 scalar_t__ PyInt_Check (int /*<<< orphan*/ *) ; 
 scalar_t__ PyLong_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PySequence_Fast (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * PySequence_Fast_GET_ITEM (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ PySequence_Size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_Ellipsis ; 

__attribute__((used)) static int
einsum_list_to_subscripts(PyObject *obj, char *subscripts, int subsize)
{
    int ellipsis = 0, subindex = 0;
    npy_intp i, size;
    PyObject *item;

    obj = PySequence_Fast(obj, "the subscripts for each operand must "
                               "be a list or a tuple");
    if (obj == NULL) {
        return -1;
    }
    size = PySequence_Size(obj);


    for (i = 0; i < size; ++i) {
        item = PySequence_Fast_GET_ITEM(obj, i);
        /* Ellipsis */
        if (item == Py_Ellipsis) {
            if (ellipsis) {
                PyErr_SetString(PyExc_ValueError,
                        "each subscripts list may have only one ellipsis");
                Py_DECREF(obj);
                return -1;
            }
            if (subindex + 3 >= subsize) {
                PyErr_SetString(PyExc_ValueError,
                        "subscripts list is too long");
                Py_DECREF(obj);
                return -1;
            }
            subscripts[subindex++] = '.';
            subscripts[subindex++] = '.';
            subscripts[subindex++] = '.';
            ellipsis = 1;
        }
        /* Subscript */
        else if (PyInt_Check(item) || PyLong_Check(item)) {
            long s = PyInt_AsLong(item);
            npy_bool bad_input = 0;

            if (subindex + 1 >= subsize) {
                PyErr_SetString(PyExc_ValueError,
                        "subscripts list is too long");
                Py_DECREF(obj);
                return -1;
            }

            if ( s < 0 ) {
                bad_input = 1;
            }
            else if (s < 26) {
                subscripts[subindex++] = 'A' + (char)s;
            }
            else if (s < 2*26) {
                subscripts[subindex++] = 'a' + (char)s - 26;
            }
            else {
                bad_input = 1;
            }

            if (bad_input) {
                PyErr_SetString(PyExc_ValueError,
                        "subscript is not within the valid range [0, 52)");
                Py_DECREF(obj);
                return -1;
            }
        }
        /* Invalid */
        else {
            PyErr_SetString(PyExc_ValueError,
                    "each subscript must be either an integer "
                    "or an ellipsis");
            Py_DECREF(obj);
            return -1;
        }
    }

    Py_DECREF(obj);

    return subindex;
}