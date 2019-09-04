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
struct TYPE_3__ {int /*<<< orphan*/  fields; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ PyArray_Descr ;

/* Variables and functions */
 int /*<<< orphan*/  PyBytes_AsString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyDict_GetItem (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_Format (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyExc_KeyError ; 
 int /*<<< orphan*/ * PyTuple_GET_ITEM (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PyUnicode_AsUnicodeEscapeString (int /*<<< orphan*/ *) ; 
 scalar_t__ PyUnicode_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyObject *
_subscript_by_name(PyArray_Descr *self, PyObject *op)
{
    PyObject *obj = PyDict_GetItem(self->fields, op);
    PyObject *descr;
    PyObject *s;

    if (obj == NULL) {
        if (PyUnicode_Check(op)) {
            s = PyUnicode_AsUnicodeEscapeString(op);
        }
        else {
            s = op;
        }

        PyErr_Format(PyExc_KeyError,
                "Field named \'%s\' not found.", PyBytes_AsString(s));
        if (s != op) {
            Py_DECREF(s);
        }
        return NULL;
    }
    descr = PyTuple_GET_ITEM(obj, 0);
    Py_INCREF(descr);
    return descr;
}