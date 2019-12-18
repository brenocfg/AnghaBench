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
typedef  int /*<<< orphan*/  npy_longlong ;
struct TYPE_3__ {scalar_t__ size; scalar_t__ index; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ PyArrayMultiIterObject ;

/* Variables and functions */
 scalar_t__ NPY_MAX_LONG ; 
 int /*<<< orphan*/ * PyInt_FromLong (long) ; 
 int /*<<< orphan*/ * PyLong_FromLongLong (int /*<<< orphan*/ ) ; 

__attribute__((used)) static PyObject *
arraymultiter_index_get(PyArrayMultiIterObject *self)
{
#if NPY_SIZEOF_INTP <= NPY_SIZEOF_LONG
    return PyInt_FromLong((long) self->index);
#else
    if (self->size < NPY_MAX_LONG) {
        return PyInt_FromLong((long) self->index);
    }
    else {
        return PyLong_FromLongLong((npy_longlong) self->index);
    }
#endif
}