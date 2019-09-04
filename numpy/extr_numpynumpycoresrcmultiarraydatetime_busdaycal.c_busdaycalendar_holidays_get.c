#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int npy_intp ;
typedef  int /*<<< orphan*/  npy_datetime ;
struct TYPE_4__ {int end; int begin; } ;
struct TYPE_5__ {TYPE_1__ holidays; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyArray_Descr ;
typedef  int /*<<< orphan*/  PyArrayObject ;
typedef  TYPE_2__ NpyBusDayCalendar ;

/* Variables and functions */
 int /*<<< orphan*/  NPY_DATETIME ; 
 int /*<<< orphan*/  NPY_FR_D ; 
 int /*<<< orphan*/  PyArray_DATA (int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_SimpleNewFromDescr (int,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * create_datetime_dtype_with_unit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static PyObject *
busdaycalendar_holidays_get(NpyBusDayCalendar *self)
{
    PyArrayObject *ret;
    PyArray_Descr *date_dtype;
    npy_intp size = self->holidays.end - self->holidays.begin;

    /* Create a date dtype */
    date_dtype = create_datetime_dtype_with_unit(NPY_DATETIME, NPY_FR_D);
    if (date_dtype == NULL) {
        return NULL;
    }

    /* Allocate a date array (this steals the date_dtype reference) */
    ret = (PyArrayObject *)PyArray_SimpleNewFromDescr(1, &size, date_dtype);
    if (ret == NULL) {
        return NULL;
    }

    /* Copy the holidays */
    if (size > 0) {
        memcpy(PyArray_DATA(ret), self->holidays.begin,
                    size * sizeof(npy_datetime));
    }

    return (PyObject *)ret;
}