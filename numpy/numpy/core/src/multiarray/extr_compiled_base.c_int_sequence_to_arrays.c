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
 int /*<<< orphan*/  PyErr_Format (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 int /*<<< orphan*/  PySequence_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PySequence_GetItem (int /*<<< orphan*/ *,int) ; 
 int PySequence_Size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * astype_anyint (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int int_sequence_to_arrays(PyObject *seq,
                              char *paramname,
                              int count,
                              PyArrayObject **op
                              )
{
    int i;

    if (!PySequence_Check(seq) || PySequence_Size(seq) != count) {
        PyErr_Format(PyExc_ValueError,
                "parameter %s must be a sequence of length %d",
                paramname, count);
        return -1;
    }

    for (i = 0; i < count; ++i) {
        PyObject *item = PySequence_GetItem(seq, i);
        if (item == NULL) {
            goto fail;
        }
        op[i] = astype_anyint(item);
        Py_DECREF(item);
        if (op[i] == NULL) {
            goto fail;
        }
    }

    return 0;

fail:
    while (--i >= 0) {
        Py_XDECREF(op[i]);
        op[i] = NULL;
    }
    return -1;
}