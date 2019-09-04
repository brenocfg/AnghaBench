#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  elsize; } ;
struct TYPE_8__ {scalar_t__ ao; } ;
struct TYPE_7__ {TYPE_3__* _internal_iter; } ;
struct TYPE_6__ {int flags; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ PyArrayObject_fields ;
typedef  int /*<<< orphan*/  PyArrayObject ;
typedef  TYPE_2__ PyArrayNeighborhoodIterObject ;
typedef  TYPE_3__ PyArrayIterObject ;

/* Variables and functions */
 int /*<<< orphan*/  NPY_ARRAY_BEHAVED ; 
 int /*<<< orphan*/  PyArray_DATA (int /*<<< orphan*/ *) ; 
 TYPE_5__* PyArray_DESCR (scalar_t__) ; 
 int /*<<< orphan*/  PyArray_ENABLEFLAGS (scalar_t__,int /*<<< orphan*/ ) ; 
 int PyArray_FLAGS (scalar_t__) ; 
 scalar_t__ PyArray_ISOBJECT (scalar_t__) ; 
 int PyArray_SETITEM (scalar_t__,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyDataMem_FREE (char*) ; 
 char* PyDataMem_NEW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyErr_SetNone (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyExc_MemoryError ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static char* _set_constant(PyArrayNeighborhoodIterObject* iter,
        PyArrayObject *fill)
{
    char *ret;
    PyArrayIterObject *ar = iter->_internal_iter;
    int storeflags, st;

    ret = PyDataMem_NEW(PyArray_DESCR(ar->ao)->elsize);
    if (ret == NULL) {
        PyErr_SetNone(PyExc_MemoryError);
        return NULL;
    }

    if (PyArray_ISOBJECT(ar->ao)) {
        memcpy(ret, PyArray_DATA(fill), sizeof(PyObject*));
        Py_INCREF(*(PyObject**)ret);
    } else {
        /* Non-object types */

        storeflags = PyArray_FLAGS(ar->ao);
        PyArray_ENABLEFLAGS(ar->ao, NPY_ARRAY_BEHAVED);
        st = PyArray_SETITEM(ar->ao, ret, (PyObject*)fill);
        ((PyArrayObject_fields *)ar->ao)->flags = storeflags;

        if (st < 0) {
            PyDataMem_FREE(ret);
            return NULL;
        }
    }

    return ret;
}