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
struct TYPE_2__ {int /*<<< orphan*/  data_finish_src; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ _one_to_n_data ;
typedef  int /*<<< orphan*/  NpyAuxData ;

/* Variables and functions */
 int /*<<< orphan*/  NPY_AUXDATA_FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyArray_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void _one_to_n_data_free(NpyAuxData *data)
{
    _one_to_n_data *d = (_one_to_n_data *)data;
    NPY_AUXDATA_FREE(d->data);
    NPY_AUXDATA_FREE(d->data_finish_src);
    PyArray_free(data);
}