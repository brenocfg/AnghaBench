#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ shape; int /*<<< orphan*/  base; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* tp_free ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_7__ {scalar_t__ fields; int type_num; int type; scalar_t__ typeobj; scalar_t__ names; scalar_t__ metadata; int /*<<< orphan*/ * c_metadata; TYPE_6__* subarray; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ PyArray_Descr ;

/* Variables and functions */
 int /*<<< orphan*/  NPY_AUXDATA_FREE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_free (TYPE_6__*) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Py_INCREF (TYPE_1__*) ; 
 scalar_t__ Py_None ; 
 TYPE_3__* Py_TYPE (TYPE_1__*) ; 
 int /*<<< orphan*/  Py_XDECREF (scalar_t__) ; 
 int /*<<< orphan*/  _dealloc_cached_buffer_info (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
arraydescr_dealloc(PyArray_Descr *self)
{
    if (self->fields == Py_None) {
        fprintf(stderr, "*** Reference count error detected: \n" \
                "an attempt was made to deallocate %d (%c) ***\n",
                self->type_num, self->type);
        Py_INCREF(self);
        Py_INCREF(self);
        return;
    }
    _dealloc_cached_buffer_info((PyObject*)self);
    Py_XDECREF(self->typeobj);
    Py_XDECREF(self->names);
    Py_XDECREF(self->fields);
    if (self->subarray) {
        Py_XDECREF(self->subarray->shape);
        Py_DECREF(self->subarray->base);
        PyArray_free(self->subarray);
    }
    Py_XDECREF(self->metadata);
    NPY_AUXDATA_FREE(self->c_metadata);
    self->c_metadata = NULL;
    Py_TYPE(self)->tp_free((PyObject *)self);
}