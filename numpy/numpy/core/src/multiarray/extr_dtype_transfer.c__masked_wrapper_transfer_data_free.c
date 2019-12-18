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
struct TYPE_2__ {int /*<<< orphan*/  decsrcref_transferdata; int /*<<< orphan*/  transferdata; } ;
typedef  TYPE_1__ _masked_wrapper_transfer_data ;
typedef  int /*<<< orphan*/  NpyAuxData ;

/* Variables and functions */
 int /*<<< orphan*/  NPY_AUXDATA_FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyArray_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void _masked_wrapper_transfer_data_free(NpyAuxData *data)
{
    _masked_wrapper_transfer_data *d = (_masked_wrapper_transfer_data *)data;
    NPY_AUXDATA_FREE(d->transferdata);
    NPY_AUXDATA_FREE(d->decsrcref_transferdata);
    PyArray_free(data);
}