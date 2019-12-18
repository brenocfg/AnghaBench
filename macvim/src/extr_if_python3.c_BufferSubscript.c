#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* buf; } ;
struct TYPE_7__ {scalar_t__ ml_line_count; } ;
struct TYPE_8__ {TYPE_1__ b_ml; } ;
typedef  int /*<<< orphan*/  Py_ssize_t ;
typedef  int /*<<< orphan*/  PySliceObject_T ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_3__ BufferObject ;

/* Variables and functions */
 int /*<<< orphan*/ * BufferItem (TYPE_3__*,long) ; 
 int /*<<< orphan*/ * BufferSlice (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ CheckBuffer (TYPE_3__*) ; 
 long PyLong_AsLong (int /*<<< orphan*/ *) ; 
 scalar_t__ PyLong_Check (int /*<<< orphan*/ *) ; 
 scalar_t__ PySlice_Check (int /*<<< orphan*/ *) ; 
 scalar_t__ PySlice_GetIndicesEx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RAISE_INVALID_INDEX_TYPE (int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyObject *
BufferSubscript(PyObject *self, PyObject* idx)
{
    if (PyLong_Check(idx))
    {
	long _idx = PyLong_AsLong(idx);
	return BufferItem((BufferObject *)(self), _idx);
    } else if (PySlice_Check(idx))
    {
	Py_ssize_t start, stop, step, slicelen;

	if (CheckBuffer((BufferObject *) self))
	    return NULL;

	if (PySlice_GetIndicesEx((PySliceObject_T *)idx,
	      (Py_ssize_t)((BufferObject *)(self))->buf->b_ml.ml_line_count,
	      &start, &stop,
	      &step, &slicelen) < 0)
	{
	    return NULL;
	}
	return BufferSlice((BufferObject *)(self), start, stop);
    }
    else
    {
	RAISE_INVALID_INDEX_TYPE(idx);
	return NULL;
    }
}