#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * end; int /*<<< orphan*/ * begin; } ;
struct TYPE_5__ {int busdays_in_weekmask; int* weekmask; TYPE_2__ holidays; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ NpyBusDayCalendar ;

/* Variables and functions */
 int /*<<< orphan*/  PyArg_ParseTupleAndKeywords (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char**,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  PyArray_HolidaysConverter ; 
 int /*<<< orphan*/  PyArray_WeekMaskConverter ; 
 int /*<<< orphan*/  PyArray_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 int /*<<< orphan*/  normalize_holidays_list (TYPE_2__*,int*) ; 

__attribute__((used)) static int
busdaycalendar_init(NpyBusDayCalendar *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"weekmask", "holidays", NULL};
    int i, busdays_in_weekmask;

    /* Clear the holidays if necessary */
    if (self->holidays.begin != NULL) {
        PyArray_free(self->holidays.begin);
        self->holidays.begin = NULL;
        self->holidays.end = NULL;
    }

    /* Reset the weekmask to the default */
    self->busdays_in_weekmask = 5;
    self->weekmask[0] = 1;
    self->weekmask[1] = 1;
    self->weekmask[2] = 1;
    self->weekmask[3] = 1;
    self->weekmask[4] = 1;
    self->weekmask[5] = 0;
    self->weekmask[6] = 0;

    /* Parse the parameters */
    if (!PyArg_ParseTupleAndKeywords(args, kwds,
                        "|O&O&:busdaycal", kwlist,
                        &PyArray_WeekMaskConverter, &self->weekmask[0],
                        &PyArray_HolidaysConverter, &self->holidays)) {
        return -1;
    }

    /* Count the number of business days in a week */
    busdays_in_weekmask = 0;
    for (i = 0; i < 7; ++i) {
        busdays_in_weekmask += self->weekmask[i];
    }
    self->busdays_in_weekmask = busdays_in_weekmask;

    /* Normalize the holidays list */
    normalize_holidays_list(&self->holidays, self->weekmask);

    if (self->busdays_in_weekmask == 0) {
        PyErr_SetString(PyExc_ValueError,
                "Cannot construct a numpy.busdaycal with a weekmask of "
                "all zeros");
        return -1;
    }

    return 0;
}