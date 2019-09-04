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
 scalar_t__ NPY_FAIL ; 
 int /*<<< orphan*/  PyArray_CanCastTo (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_DescrCheck (int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_DescrConverter (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  PyArray_EquivTypes (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
#define  Py_EQ 133 
 int /*<<< orphan*/ * Py_False ; 
#define  Py_GE 132 
#define  Py_GT 131 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 
#define  Py_LE 130 
#define  Py_LT 129 
#define  Py_NE 128 
 int /*<<< orphan*/ * Py_NotImplemented ; 
 int /*<<< orphan*/ * Py_True ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyObject *
arraydescr_richcompare(PyArray_Descr *self, PyObject *other, int cmp_op)
{
    PyArray_Descr *new = NULL;
    PyObject *result = Py_NotImplemented;
    if (!PyArray_DescrCheck(other)) {
        if (PyArray_DescrConverter(other, &new) == NPY_FAIL) {
            return NULL;
        }
    }
    else {
        new = (PyArray_Descr *)other;
        Py_INCREF(new);
    }
    switch (cmp_op) {
    case Py_LT:
        if (!PyArray_EquivTypes(self, new) && PyArray_CanCastTo(self, new)) {
            result = Py_True;
        }
        else {
            result = Py_False;
        }
        break;
    case Py_LE:
        if (PyArray_CanCastTo(self, new)) {
            result = Py_True;
        }
        else {
            result = Py_False;
        }
        break;
    case Py_EQ:
        if (PyArray_EquivTypes(self, new)) {
            result = Py_True;
        }
        else {
            result = Py_False;
        }
        break;
    case Py_NE:
        if (PyArray_EquivTypes(self, new))
            result = Py_False;
        else
            result = Py_True;
        break;
    case Py_GT:
        if (!PyArray_EquivTypes(self, new) && PyArray_CanCastTo(new, self)) {
            result = Py_True;
        }
        else {
            result = Py_False;
        }
        break;
    case Py_GE:
        if (PyArray_CanCastTo(new, self)) {
            result = Py_True;
        }
        else {
            result = Py_False;
        }
        break;
    default:
        result = Py_NotImplemented;
    }

    Py_XDECREF(new);
    Py_INCREF(result);
    return result;
}