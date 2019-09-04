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
struct TYPE_3__ {int /*<<< orphan*/  alignment; int /*<<< orphan*/  elsize; int /*<<< orphan*/  flags; int /*<<< orphan*/  kind; int /*<<< orphan*/  byteorder; } ;
typedef  scalar_t__ Py_ssize_t ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ PyArray_Descr ;

/* Variables and functions */
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_SystemError ; 
 int /*<<< orphan*/  PyList_Append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyTuple_GetItem (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ PyTuple_Size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_BuildValue (char*,int /*<<< orphan*/ ,char,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 char _normalize_byteorder (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _array_descr_builtin(PyArray_Descr* descr, PyObject *l)
{
    Py_ssize_t i;
    PyObject *t, *item;
    char nbyteorder = _normalize_byteorder(descr->byteorder);

    /*
     * For builtin type, hash relies on : kind + byteorder + flags +
     * type_num + elsize + alignment
     */
    t = Py_BuildValue("(cccii)", descr->kind, nbyteorder,
            descr->flags, descr->elsize, descr->alignment);

    for(i = 0; i < PyTuple_Size(t); ++i) {
        item = PyTuple_GetItem(t, i);
        if (item == NULL) {
            PyErr_SetString(PyExc_SystemError,
                    "(Hash) Error while computing builting hash");
            goto clean_t;
        }
        PyList_Append(l, item);
    }

    Py_DECREF(t);
    return 0;

clean_t:
    Py_DECREF(t);
    return -1;
}