#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * transferdata; int /*<<< orphan*/ * decsrcref_transferdata; } ;
typedef  TYPE_1__ _masked_wrapper_transfer_data ;
typedef  int /*<<< orphan*/  NpyAuxData ;

/* Variables and functions */
 void* NPY_AUXDATA_CLONE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NPY_AUXDATA_FREE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_free (TYPE_1__*) ; 
 scalar_t__ PyArray_malloc (int) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 

__attribute__((used)) static NpyAuxData *_masked_wrapper_transfer_data_clone(NpyAuxData *data)
{
    _masked_wrapper_transfer_data *d = (_masked_wrapper_transfer_data *)data;
    _masked_wrapper_transfer_data *newdata;

    /* Allocate the data and populate it */
    newdata = (_masked_wrapper_transfer_data *)PyArray_malloc(
                                    sizeof(_masked_wrapper_transfer_data));
    if (newdata == NULL) {
        return NULL;
    }
    memcpy(newdata, d, sizeof(_masked_wrapper_transfer_data));

    /* Clone all the owned auxdata as well */
    if (newdata->transferdata != NULL) {
        newdata->transferdata = NPY_AUXDATA_CLONE(newdata->transferdata);
        if (newdata->transferdata == NULL) {
            PyArray_free(newdata);
            return NULL;
        }
    }
    if (newdata->decsrcref_transferdata != NULL) {
        newdata->decsrcref_transferdata =
                        NPY_AUXDATA_CLONE(newdata->decsrcref_transferdata);
        if (newdata->decsrcref_transferdata == NULL) {
            NPY_AUXDATA_FREE(newdata->transferdata);
            PyArray_free(newdata);
            return NULL;
        }
    }

    return (NpyAuxData *)newdata;
}