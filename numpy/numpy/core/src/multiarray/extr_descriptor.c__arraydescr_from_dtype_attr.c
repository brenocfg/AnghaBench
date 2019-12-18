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
typedef  int /*<<< orphan*/  PyArray_Descr ;

/* Variables and functions */
 int NPY_SUCCEED ; 
 int PyArray_DescrConverter (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  PyErr_Clear () ; 
 int /*<<< orphan*/  PyErr_ExceptionMatches (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyExc_RecursionError ; 
 int /*<<< orphan*/ * PyObject_GetAttrString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 scalar_t__ Py_EnterRecursiveCall (char*) ; 
 int /*<<< orphan*/  Py_LeaveRecursiveCall () ; 

int
_arraydescr_from_dtype_attr(PyObject *obj, PyArray_Descr **newdescr)
{
    PyObject *dtypedescr;
    int ret;

    /* For arbitrary objects that have a "dtype" attribute */
    dtypedescr = PyObject_GetAttrString(obj, "dtype");
    if (dtypedescr == NULL) {
        /*
         * This can be reached due to recursion limit being hit while fetching
         * the attribute (tested for py3.7). This removes the custom message.
         */
        goto fail;
    }

    if (Py_EnterRecursiveCall(
            " while trying to convert the given data type from its "
            "`.dtype` attribute.") != 0) {
        Py_DECREF(dtypedescr);
        return 1;
    }

    ret = PyArray_DescrConverter(dtypedescr, newdescr);

    Py_DECREF(dtypedescr);
    Py_LeaveRecursiveCall();
    if (ret != NPY_SUCCEED) {
        goto fail;
    }

    return 1;

  fail:
    /* Ignore all but recursion errors, to give ctypes a full try. */
    if (!PyErr_ExceptionMatches(PyExc_RecursionError)) {
        PyErr_Clear();
        return 0;
    }
    return 1;
}