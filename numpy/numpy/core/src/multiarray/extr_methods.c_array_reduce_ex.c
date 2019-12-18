#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ elsize; } ;
struct TYPE_10__ {int /*<<< orphan*/ * ob_type; } ;
typedef  TYPE_1__ PyObject ;
typedef  TYPE_2__ PyArray_Descr ;
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 int /*<<< orphan*/  NPY_ITEM_HASOBJECT ; 
 int /*<<< orphan*/  PyArg_ParseTuple (TYPE_1__*,char*,int*) ; 
 TYPE_2__* PyArray_DESCR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_IS_C_CONTIGUOUS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_IS_F_CONTIGUOUS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_Type ; 
 scalar_t__ PyDataType_FLAGCHK (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyErr_Format (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 scalar_t__ PyType_IsSubtype (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* array_reduce_ex_picklebuffer (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* array_reduce_ex_regular (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static PyObject *
array_reduce_ex(PyArrayObject *self, PyObject *args)
{
    int protocol;
    PyArray_Descr *descr = NULL;

    if (!PyArg_ParseTuple(args, "i", &protocol)) {
        return NULL;
    }

    descr = PyArray_DESCR(self);
    if ((protocol < 5) ||
        (!PyArray_IS_C_CONTIGUOUS((PyArrayObject*)self) &&
         !PyArray_IS_F_CONTIGUOUS((PyArrayObject*)self)) ||
        PyDataType_FLAGCHK(descr, NPY_ITEM_HASOBJECT) ||
        (PyType_IsSubtype(((PyObject*)self)->ob_type, &PyArray_Type) &&
         ((PyObject*)self)->ob_type != &PyArray_Type) ||
        descr->elsize == 0) {
        /* The PickleBuffer class from version 5 of the pickle protocol
         * can only be used for arrays backed by a contiguous data buffer.
         * For all other cases we fallback to the generic array_reduce
         * method that involves using a temporary bytes allocation. */
        return array_reduce_ex_regular(self, protocol);
    }
    else if (protocol == 5) {
        return array_reduce_ex_picklebuffer(self, protocol);
    }
    else {
        PyErr_Format(PyExc_ValueError,
                     "__reduce_ex__ called with protocol > 5");
        return NULL;
    }
}