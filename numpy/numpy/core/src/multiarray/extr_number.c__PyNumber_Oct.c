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
 int /*<<< orphan*/ * PyImport_ImportModule (char*) ; 
 int /*<<< orphan*/ * PyObject_CallMethod (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyObject *
_PyNumber_Oct(PyObject *o) {
    PyObject *res;
    PyObject *mod = PyImport_ImportModule("__builtin__");
    if (mod == NULL) {
        return NULL;
    }
    res = PyObject_CallMethod(mod, "oct", "(O)", o);
    Py_DECREF(mod);
    return res;
}