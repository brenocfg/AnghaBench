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
struct TYPE_2__ {int /*<<< orphan*/  fromdata; int /*<<< orphan*/  todata; int /*<<< orphan*/  wrappeddata; } ;
typedef  TYPE_1__ _align_wrap_data ;
typedef  int /*<<< orphan*/  NpyAuxData ;

/* Variables and functions */
 int /*<<< orphan*/  NPY_AUXDATA_FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyArray_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void _align_wrap_data_free(NpyAuxData *data)
{
    _align_wrap_data *d = (_align_wrap_data *)data;
    NPY_AUXDATA_FREE(d->wrappeddata);
    NPY_AUXDATA_FREE(d->todata);
    NPY_AUXDATA_FREE(d->fromdata);
    PyArray_free(data);
}