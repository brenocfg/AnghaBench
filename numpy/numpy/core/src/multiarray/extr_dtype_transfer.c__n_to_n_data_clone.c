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
struct TYPE_4__ {int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ _n_to_n_data ;
typedef  int /*<<< orphan*/  NpyAuxData ;

/* Variables and functions */
 int /*<<< orphan*/ * NPY_AUXDATA_CLONE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_free (TYPE_1__*) ; 
 scalar_t__ PyArray_malloc (int) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static NpyAuxData *_n_to_n_data_clone(NpyAuxData *data)
{
    _n_to_n_data *d = (_n_to_n_data *)data;
    _n_to_n_data *newdata;

    /* Allocate the data, and populate it */
    newdata = (_n_to_n_data *)PyArray_malloc(sizeof(_n_to_n_data));
    if (newdata == NULL) {
        return NULL;
    }
    memcpy(newdata, data, sizeof(_n_to_n_data));
    if (newdata->data != NULL) {
        newdata->data = NPY_AUXDATA_CLONE(d->data);
        if (newdata->data == NULL) {
            PyArray_free(newdata);
            return NULL;
        }
    }

    return (NpyAuxData *)newdata;
}