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
typedef  int npy_intp ;
struct TYPE_3__ {int /*<<< orphan*/  weekmask; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyArrayObject ;
typedef  TYPE_1__ NpyBusDayCalendar ;

/* Variables and functions */
 int /*<<< orphan*/  NPY_BOOL ; 
 int /*<<< orphan*/  PyArray_DATA (int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_SimpleNew (int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static PyObject *
busdaycalendar_weekmask_get(NpyBusDayCalendar *self)
{
    PyArrayObject *ret;
    npy_intp size = 7;

    /* Allocate a 7-element boolean array */
    ret = (PyArrayObject *)PyArray_SimpleNew(1, &size, NPY_BOOL);
    if (ret == NULL) {
        return NULL;
    }

    /* Copy the weekmask data */
    memcpy(PyArray_DATA(ret), self->weekmask, 7);

    return (PyObject *)ret;
}