#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char flags; int alignment; int elsize; int /*<<< orphan*/ * names; int /*<<< orphan*/ * fields; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ PyArray_Descr ;

/* Variables and functions */
 char NPY_ALIGNED_STRUCT ; 
 int NPY_FAIL ; 
 char NPY_FROM_FIELDS ; 
 char NPY_NEEDS_PYAPI ; 
 int NPY_NEXT_ALIGNED_OFFSET (int,int) ; 
 int /*<<< orphan*/  NPY_VOID ; 
 int PyArray_DescrAlignConverter (int /*<<< orphan*/ *,TYPE_1__**) ; 
 int PyArray_DescrConverter (int /*<<< orphan*/ *,TYPE_1__**) ; 
 TYPE_1__* PyArray_DescrNewFromType (int /*<<< orphan*/ ) ; 
 int PyArray_MAX (int,int) ; 
 scalar_t__ PyBytes_Check (int /*<<< orphan*/ *) ; 
 scalar_t__ PyBytes_GET_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyDict_New () ; 
 int /*<<< orphan*/  PyDict_SetItem (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyInt_FromLong (long) ; 
 int /*<<< orphan*/ * PyList_GET_ITEM (int /*<<< orphan*/ *,int) ; 
 int PyList_GET_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyTuple_New (int) ; 
 int /*<<< orphan*/  PyTuple_SET_ITEM (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyUString_FromFormat (char*,int) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyArray_Descr *
_convert_from_list(PyObject *obj, int align)
{
    int n, i;
    int totalsize;
    PyObject *fields;
    PyArray_Descr *conv = NULL;
    PyArray_Descr *new;
    PyObject *key, *tup;
    PyObject *nameslist = NULL;
    int ret;
    int maxalign = 0;
    /* Types with fields need the Python C API for field access */
    char dtypeflags = NPY_NEEDS_PYAPI;

    n = PyList_GET_SIZE(obj);
    /*
     * Ignore any empty string at end which _internal._commastring
     * can produce
     */
    key = PyList_GET_ITEM(obj, n-1);
    if (PyBytes_Check(key) && PyBytes_GET_SIZE(key) == 0) {
        n = n - 1;
    }
    /* End ignore code.*/
    totalsize = 0;
    if (n == 0) {
        return NULL;
    }
    nameslist = PyTuple_New(n);
    if (!nameslist) {
        return NULL;
    }
    fields = PyDict_New();
    for (i = 0; i < n; i++) {
        tup = PyTuple_New(2);
        key = PyUString_FromFormat("f%d", i);
        if (align) {
            ret = PyArray_DescrAlignConverter(PyList_GET_ITEM(obj, i), &conv);
        }
        else {
            ret = PyArray_DescrConverter(PyList_GET_ITEM(obj, i), &conv);
        }
        if (ret == NPY_FAIL) {
            Py_DECREF(tup);
            Py_DECREF(key);
            goto fail;
        }
        dtypeflags |= (conv->flags & NPY_FROM_FIELDS);
        PyTuple_SET_ITEM(tup, 0, (PyObject *)conv);
        if (align) {
            int _align;

            _align = conv->alignment;
            if (_align > 1) {
                totalsize = NPY_NEXT_ALIGNED_OFFSET(totalsize, _align);
            }
            maxalign = PyArray_MAX(maxalign, _align);
        }
        PyTuple_SET_ITEM(tup, 1, PyInt_FromLong((long) totalsize));
        PyDict_SetItem(fields, key, tup);
        Py_DECREF(tup);
        PyTuple_SET_ITEM(nameslist, i, key);
        totalsize += conv->elsize;
    }
    new = PyArray_DescrNewFromType(NPY_VOID);
    new->fields = fields;
    new->names = nameslist;
    new->flags = dtypeflags;
    if (maxalign > 1) {
        totalsize = NPY_NEXT_ALIGNED_OFFSET(totalsize, maxalign);
    }
    /* Structured arrays get a sticky aligned bit */
    if (align) {
        new->flags |= NPY_ALIGNED_STRUCT;
        new->alignment = maxalign;
    }
    new->elsize = totalsize;
    return new;

 fail:
    Py_DECREF(nameslist);
    Py_DECREF(fields);
    return NULL;
}