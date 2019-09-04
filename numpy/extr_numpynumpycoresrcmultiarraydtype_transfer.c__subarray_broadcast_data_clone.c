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
typedef  int npy_intp ;
typedef  int /*<<< orphan*/  _subarray_broadcast_offsetrun ;
struct TYPE_4__ {int run_count; int /*<<< orphan*/ * data_decsrcref; int /*<<< orphan*/ * data; int /*<<< orphan*/ * data_decdstref; } ;
typedef  TYPE_1__ _subarray_broadcast_data ;
typedef  int /*<<< orphan*/  NpyAuxData ;

/* Variables and functions */
 void* NPY_AUXDATA_CLONE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NPY_AUXDATA_FREE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_free (TYPE_1__*) ; 
 scalar_t__ PyArray_malloc (int) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static NpyAuxData *_subarray_broadcast_data_clone( NpyAuxData *data)
{
    _subarray_broadcast_data *d = (_subarray_broadcast_data *)data;
    _subarray_broadcast_data *newdata;
    npy_intp run_count = d->run_count, structsize;

    structsize = sizeof(_subarray_broadcast_data) +
                        run_count*sizeof(_subarray_broadcast_offsetrun);

    /* Allocate the data and populate it */
    newdata = (_subarray_broadcast_data *)PyArray_malloc(structsize);
    if (newdata == NULL) {
        return NULL;
    }
    memcpy(newdata, data, structsize);
    if (d->data != NULL) {
        newdata->data = NPY_AUXDATA_CLONE(d->data);
        if (newdata->data == NULL) {
            PyArray_free(newdata);
            return NULL;
        }
    }
    if (d->data_decsrcref != NULL) {
        newdata->data_decsrcref = NPY_AUXDATA_CLONE(d->data_decsrcref);
        if (newdata->data_decsrcref == NULL) {
            NPY_AUXDATA_FREE(newdata->data);
            PyArray_free(newdata);
            return NULL;
        }
    }
    if (d->data_decdstref != NULL) {
        newdata->data_decdstref = NPY_AUXDATA_CLONE(d->data_decdstref);
        if (newdata->data_decdstref == NULL) {
            NPY_AUXDATA_FREE(newdata->data);
            NPY_AUXDATA_FREE(newdata->data_decsrcref);
            PyArray_free(newdata);
            return NULL;
        }
    }

    return (NpyAuxData *)newdata;
}