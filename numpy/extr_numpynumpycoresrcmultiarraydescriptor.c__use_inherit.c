#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ elsize; int /*<<< orphan*/  flags; int /*<<< orphan*/ * metadata; int /*<<< orphan*/ * names; int /*<<< orphan*/ * fields; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ PyArray_Descr ;

/* Variables and functions */
 int /*<<< orphan*/  Integer ; 
 int /*<<< orphan*/  PyArray_DescrConverter (int /*<<< orphan*/ *,TYPE_1__**) ; 
 TYPE_1__* PyArray_DescrNew (TYPE_1__*) ; 
 scalar_t__ PyArray_IsScalar (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ PyDataType_HASFIELDS (TYPE_1__*) ; 
 scalar_t__ PyDataType_ISUNSIZED (TYPE_1__*) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 int /*<<< orphan*/  Py_DECREF (TYPE_1__*) ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_XINCREF (int /*<<< orphan*/ *) ; 
 scalar_t__ _is_tuple_of_integers (int /*<<< orphan*/ *) ; 
 scalar_t__ invalid_union_object_dtype (TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static PyArray_Descr *
_use_inherit(PyArray_Descr *type, PyObject *newobj, int *errflag)
{
    PyArray_Descr *new;
    PyArray_Descr *conv;

    *errflag = 0;
    if (PyArray_IsScalar(newobj, Integer)
            || _is_tuple_of_integers(newobj)
            || !PyArray_DescrConverter(newobj, &conv)) {
        return NULL;
    }
    *errflag = 1;
    new = PyArray_DescrNew(type);
    if (new == NULL) {
        goto fail;
    }
    if (PyDataType_ISUNSIZED(new)) {
        new->elsize = conv->elsize;
    }
    else if (new->elsize != conv->elsize) {
        PyErr_SetString(PyExc_ValueError,
                "mismatch in size of old and new data-descriptor");
        Py_DECREF(new);
        goto fail;
    }
    else if (invalid_union_object_dtype(new, conv)) {
        Py_DECREF(new);
        goto fail;
    }

    if (PyDataType_HASFIELDS(conv)) {
        Py_XDECREF(new->fields);
        new->fields = conv->fields;
        Py_XINCREF(new->fields);

        Py_XDECREF(new->names);
        new->names = conv->names;
        Py_XINCREF(new->names);
    }
    if (conv->metadata != NULL) {
        Py_XDECREF(new->metadata);
        new->metadata = conv->metadata;
        Py_XINCREF(new->metadata);
    }
    new->flags = conv->flags;
    Py_DECREF(conv);
    *errflag = 0;
    return new;

 fail:
    Py_DECREF(conv);
    return NULL;
}