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

/* Variables and functions */
 int /*<<< orphan*/  A ; 
 int /*<<< orphan*/  ALIGNED ; 
 int /*<<< orphan*/  C ; 
 int /*<<< orphan*/  CONTIGUOUS ; 
 int /*<<< orphan*/  C_CONTIGUOUS ; 
 int /*<<< orphan*/  F ; 
 int /*<<< orphan*/  FORTRAN ; 
 int /*<<< orphan*/  F_CONTIGUOUS ; 
 int /*<<< orphan*/  NPY_ARRAY_ALIGNED ; 
 int /*<<< orphan*/  NPY_ARRAY_C_CONTIGUOUS ; 
 int /*<<< orphan*/  NPY_ARRAY_F_CONTIGUOUS ; 
 int /*<<< orphan*/  NPY_ARRAY_OWNDATA ; 
 int /*<<< orphan*/  NPY_ARRAY_UPDATEIFCOPY ; 
 int /*<<< orphan*/  NPY_ARRAY_WRITEABLE ; 
 int /*<<< orphan*/  NPY_ARRAY_WRITEBACKIFCOPY ; 
 int /*<<< orphan*/  O ; 
 int /*<<< orphan*/  OWNDATA ; 
 int /*<<< orphan*/ * PyDict_New () ; 
 int /*<<< orphan*/  PyDict_SetItemString (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  U ; 
 int /*<<< orphan*/  UPDATEIFCOPY ; 
 int /*<<< orphan*/  W ; 
 int /*<<< orphan*/  WRITEABLE ; 
 int /*<<< orphan*/  WRITEBACKIFCOPY ; 
 int /*<<< orphan*/  X ; 
 int /*<<< orphan*/  _addnew (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _addone (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
set_flaginfo(PyObject *d)
{
    PyObject *s;
    PyObject *newd;

    newd = PyDict_New();

#define _addnew(key, val, one)                                       \
    PyDict_SetItemString(newd, #key, s=PyInt_FromLong(val));    \
    Py_DECREF(s);                                               \
    PyDict_SetItemString(newd, #one, s=PyInt_FromLong(val));    \
    Py_DECREF(s)

#define _addone(key, val)                                            \
    PyDict_SetItemString(newd, #key, s=PyInt_FromLong(val));    \
    Py_DECREF(s)

    _addnew(OWNDATA, NPY_ARRAY_OWNDATA, O);
    _addnew(FORTRAN, NPY_ARRAY_F_CONTIGUOUS, F);
    _addnew(CONTIGUOUS, NPY_ARRAY_C_CONTIGUOUS, C);
    _addnew(ALIGNED, NPY_ARRAY_ALIGNED, A);
    _addnew(UPDATEIFCOPY, NPY_ARRAY_UPDATEIFCOPY, U);
    _addnew(WRITEBACKIFCOPY, NPY_ARRAY_WRITEBACKIFCOPY, X);
    _addnew(WRITEABLE, NPY_ARRAY_WRITEABLE, W);
    _addone(C_CONTIGUOUS, NPY_ARRAY_C_CONTIGUOUS);
    _addone(F_CONTIGUOUS, NPY_ARRAY_F_CONTIGUOUS);

#undef _addone
#undef _addnew

    PyDict_SetItemString(d, "_flagdict", newd);
    Py_DECREF(newd);
    return;
}