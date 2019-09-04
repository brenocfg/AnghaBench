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
typedef  size_t npy_intp ;
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ _single_field_transfer ;
struct TYPE_5__ {size_t field_count; TYPE_1__ fields; } ;
typedef  TYPE_2__ _field_transfer_data ;
typedef  int /*<<< orphan*/  NpyAuxData ;

/* Variables and functions */
 int /*<<< orphan*/  NPY_AUXDATA_FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyArray_free (TYPE_2__*) ; 

__attribute__((used)) static void _field_transfer_data_free(NpyAuxData *data)
{
    _field_transfer_data *d = (_field_transfer_data *)data;
    npy_intp i, field_count;
    _single_field_transfer *fields;

    field_count = d->field_count;
    fields = &d->fields;

    for (i = 0; i < field_count; ++i) {
        NPY_AUXDATA_FREE(fields[i].data);
    }
    PyArray_free(d);
}