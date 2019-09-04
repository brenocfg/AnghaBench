#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  tp_name; } ;
struct TYPE_5__ {int hash; int /*<<< orphan*/ * fields; int /*<<< orphan*/ * names; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ PyArray_Descr ;

/* Variables and functions */
 int /*<<< orphan*/  PyDataType_HASFIELDS (TYPE_1__*) ; 
 int PyDict_Contains (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyDict_GetItem (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyDict_New () ; 
 int /*<<< orphan*/  PyDict_SetItem (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_Clear () ; 
 int /*<<< orphan*/  PyErr_Format (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_AttributeError ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 int PyObject_Size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PySequence_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PySequence_GetItem (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * PySequence_Tuple (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyTuple_GET_ITEM (int /*<<< orphan*/ *,int) ; 
 int PyTuple_GET_SIZE (int /*<<< orphan*/ *) ; 
 int PyUString_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 TYPE_3__* Py_TYPE (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
arraydescr_names_set(PyArray_Descr *self, PyObject *val)
{
    int N = 0;
    int i;
    PyObject *new_names;
    PyObject *new_fields;

    if (val == NULL) {
        PyErr_SetString(PyExc_AttributeError,
                "Cannot delete dtype names attribute");
        return -1;
    }
    if (!PyDataType_HASFIELDS(self)) {
        PyErr_SetString(PyExc_ValueError,
                "there are no fields defined");
        return -1;
    }

    /*
     * FIXME
     *
     * This deprecation has been temporarily removed for the NumPy 1.7
     * release. It should be re-added after the 1.7 branch is done,
     * and a convenience API to replace the typical use-cases for
     * mutable names should be implemented.
     *
     * if (DEPRECATE("Setting NumPy dtype names is deprecated, the dtype "
     *                "will become immutable in a future version") < 0) {
     *     return -1;
     * }
     */

    N = PyTuple_GET_SIZE(self->names);
    if (!PySequence_Check(val) || PyObject_Size((PyObject *)val) != N) {
        PyErr_Format(PyExc_ValueError,
                "must replace all names at once with a sequence of length %d",
                N);
        return -1;
    }
    /* Make sure all entries are strings */
    for (i = 0; i < N; i++) {
        PyObject *item;
        int valid = 1;
        item = PySequence_GetItem(val, i);
        valid = PyUString_Check(item);
        Py_DECREF(item);
        if (!valid) {
            PyErr_Format(PyExc_ValueError,
                    "item #%d of names is of type %s and not string",
                    i, Py_TYPE(item)->tp_name);
            return -1;
        }
    }
    /* Invalidate cached hash value */
    self->hash = -1;
    /* Update dictionary keys in fields */
    new_names = PySequence_Tuple(val);
    new_fields = PyDict_New();
    for (i = 0; i < N; i++) {
        PyObject *key;
        PyObject *item;
        PyObject *new_key;
        int ret;
        key = PyTuple_GET_ITEM(self->names, i);
        /* Borrowed references to item and new_key */
        item = PyDict_GetItem(self->fields, key);
        new_key = PyTuple_GET_ITEM(new_names, i);
        /* Check for duplicates */
        ret = PyDict_Contains(new_fields, new_key);
        if (ret != 0) {
            if (ret < 0) {
                PyErr_Clear();
            }
            PyErr_SetString(PyExc_ValueError, "Duplicate field names given.");
            Py_DECREF(new_names);
            Py_DECREF(new_fields);
            return -1;
        }
        PyDict_SetItem(new_fields, new_key, item);
    }

    /* Replace names */
    Py_DECREF(self->names);
    self->names = new_names;

    /* Replace fields */
    Py_DECREF(self->fields);
    self->fields = new_fields;

    return 0;
}