#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * arr; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ PyArrayFlagsObject ;

/* Variables and functions */
 scalar_t__ DEPRECATE (char*) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_AttributeError ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 int /*<<< orphan*/ * PyObject_CallMethod (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PyObject_IsTrue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_False ; 
 int /*<<< orphan*/  Py_None ; 
 int /*<<< orphan*/  Py_True ; 

__attribute__((used)) static int
arrayflags_updateifcopy_set(PyArrayFlagsObject *self, PyObject *obj)
{
    PyObject *res;

    if (obj == NULL) {
        PyErr_SetString(PyExc_AttributeError,
                "Cannot delete flags updateifcopy attribute");
        return -1;
    }
    if (self->arr == NULL) {
        PyErr_SetString(PyExc_ValueError,
                "Cannot set flags on array scalars.");
        return -1;
    }
    /* 2017-Nov-10 1.14 */
    if(DEPRECATE("UPDATEIFCOPY deprecated, use WRITEBACKIFCOPY instead") < 0) {
        return -1;
    }
    res = PyObject_CallMethod(self->arr, "setflags", "OOO", Py_None, Py_None,
                              (PyObject_IsTrue(obj) ? Py_True : Py_False));
    if (res == NULL) {
        return -1;
    }
    Py_DECREF(res);
    return 0;
}