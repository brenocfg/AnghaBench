#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  data_decdstref; int /*<<< orphan*/  data_decsrcref; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ _subarray_broadcast_data ;
typedef  int /*<<< orphan*/  NpyAuxData ;

/* Variables and functions */
 int /*<<< orphan*/  NPY_AUXDATA_FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyArray_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void _subarray_broadcast_data_free(NpyAuxData *data)
{
    _subarray_broadcast_data *d = (_subarray_broadcast_data *)data;
    NPY_AUXDATA_FREE(d->data);
    NPY_AUXDATA_FREE(d->data_decsrcref);
    NPY_AUXDATA_FREE(d->data_decdstref);
    PyArray_free(data);
}