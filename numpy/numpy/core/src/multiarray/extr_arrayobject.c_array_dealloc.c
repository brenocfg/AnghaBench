#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  (* tp_free ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_3__ {int flags; int nd; int /*<<< orphan*/  descr; int /*<<< orphan*/  dimensions; scalar_t__ data; scalar_t__ base; int /*<<< orphan*/ * weakreflist; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ PyArrayObject_fields ;
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 int NPY_ARRAY_OWNDATA ; 
 int NPY_ARRAY_UPDATEIFCOPY ; 
 int NPY_ARRAY_WRITEBACKIFCOPY ; 
 int /*<<< orphan*/  NPY_ITEM_REFCOUNT ; 
 int PyArray_FLAGS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_NBYTES (int /*<<< orphan*/ *) ; 
 int PyArray_ResolveWritebackIfCopy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_XDECREF (int /*<<< orphan*/ *) ; 
 scalar_t__ PyDataType_FLAGCHK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyErr_Clear () ; 
 int /*<<< orphan*/  PyErr_Print () ; 
 int /*<<< orphan*/  PyExc_DeprecationWarning ; 
 int /*<<< orphan*/  PyExc_RuntimeWarning ; 
 int /*<<< orphan*/  PyObject_ClearWeakRefs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 
 TYPE_2__* Py_TYPE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_XDECREF (scalar_t__) ; 
 int /*<<< orphan*/  WARN_IN_DEALLOC (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  _dealloc_cached_buffer_info (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  npy_free_cache (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  npy_free_cache_dim (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
array_dealloc(PyArrayObject *self)
{
    PyArrayObject_fields *fa = (PyArrayObject_fields *)self;

    _dealloc_cached_buffer_info((PyObject*)self);

    if (fa->weakreflist != NULL) {
        PyObject_ClearWeakRefs((PyObject *)self);
    }
    if (fa->base) {
        int retval;
        if (PyArray_FLAGS(self) & NPY_ARRAY_WRITEBACKIFCOPY)
        {
            char const * msg = "WRITEBACKIFCOPY detected in array_dealloc. "
                " Required call to PyArray_ResolveWritebackIfCopy or "
                "PyArray_DiscardWritebackIfCopy is missing.";
            /*
             * prevent reaching 0 twice and thus recursing into dealloc.
             * Increasing sys.gettotalrefcount, but path should not be taken.
             */
            Py_INCREF(self);
            WARN_IN_DEALLOC(PyExc_RuntimeWarning, msg);
            retval = PyArray_ResolveWritebackIfCopy(self);
            if (retval < 0)
            {
                PyErr_Print();
                PyErr_Clear();
            }
        }
        if (PyArray_FLAGS(self) & NPY_ARRAY_UPDATEIFCOPY) {
            /* DEPRECATED, remove once the flag is removed */
            char const * msg = "UPDATEIFCOPY detected in array_dealloc. "
                " Required call to PyArray_ResolveWritebackIfCopy or "
                "PyArray_DiscardWritebackIfCopy is missing";
            /*
             * prevent reaching 0 twice and thus recursing into dealloc.
             * Increasing sys.gettotalrefcount, but path should not be taken.
             */
            Py_INCREF(self);
            /* 2017-Nov-10 1.14 */
            WARN_IN_DEALLOC(PyExc_DeprecationWarning, msg);
            retval = PyArray_ResolveWritebackIfCopy(self);
            if (retval < 0)
            {
                PyErr_Print();
                PyErr_Clear();
            }
        }
        /*
         * If fa->base is non-NULL, it is something
         * to DECREF -- either a view or a buffer object
         */
        Py_XDECREF(fa->base);
    }

    if ((fa->flags & NPY_ARRAY_OWNDATA) && fa->data) {
        /* Free internal references if an Object array */
        if (PyDataType_FLAGCHK(fa->descr, NPY_ITEM_REFCOUNT)) {
            PyArray_XDECREF(self);
        }
        npy_free_cache(fa->data, PyArray_NBYTES(self));
    }

    /* must match allocation in PyArray_NewFromDescr */
    npy_free_cache_dim(fa->dimensions, 2 * fa->nd);
    Py_DECREF(fa->descr);
    Py_TYPE(self)->tp_free((PyObject *)self);
}