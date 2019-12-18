#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  (* tp_free ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_6__ {int /*<<< orphan*/ * end; int /*<<< orphan*/ * begin; } ;
struct TYPE_7__ {TYPE_1__ holidays; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_2__ NpyBusDayCalendar ;

/* Variables and functions */
 int /*<<< orphan*/  PyArray_free (int /*<<< orphan*/ *) ; 
 TYPE_4__* Py_TYPE (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
busdaycalendar_dealloc(NpyBusDayCalendar *self)
{
    /* Clear the holidays */
    if (self->holidays.begin != NULL) {
        PyArray_free(self->holidays.begin);
        self->holidays.begin = NULL;
        self->holidays.end = NULL;
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}