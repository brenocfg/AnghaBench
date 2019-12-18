#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ start; scalar_t__ end; } ;
typedef  TYPE_1__ RangeObject ;
typedef  int /*<<< orphan*/  Py_ssize_t ;
typedef  int /*<<< orphan*/  PySliceObject_T ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 long PyLong_AsLong (int /*<<< orphan*/ *) ; 
 scalar_t__ PyLong_Check (int /*<<< orphan*/ *) ; 
 scalar_t__ PySlice_Check (int /*<<< orphan*/ *) ; 
 scalar_t__ PySlice_GetIndicesEx (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RAISE_INVALID_INDEX_TYPE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * RangeItem (TYPE_1__*,long) ; 
 int /*<<< orphan*/ * RangeSlice (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static PyObject *
RangeSubscript(PyObject *self, PyObject* idx)
{
    if (PyLong_Check(idx))
    {
	long _idx = PyLong_AsLong(idx);
	return RangeItem((RangeObject *)(self), _idx);
    } else if (PySlice_Check(idx))
    {
	Py_ssize_t start, stop, step, slicelen;

	if (PySlice_GetIndicesEx((PySliceObject_T *)idx,
		((RangeObject *)(self))->end-((RangeObject *)(self))->start+1,
		&start, &stop,
		&step, &slicelen) < 0)
	{
	    return NULL;
	}
	return RangeSlice((RangeObject *)(self), start, stop);
    }
    else
    {
	RAISE_INVALID_INDEX_TYPE(idx);
	return NULL;
    }
}