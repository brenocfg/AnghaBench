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
struct TYPE_4__ {int src_itemsize; int /*<<< orphan*/ * tmp_buffer; } ;
typedef  TYPE_1__ _strided_datetime_cast_data ;
typedef  int /*<<< orphan*/  NpyAuxData ;

/* Variables and functions */
 int /*<<< orphan*/  PyArray_free (TYPE_1__*) ; 
 int /*<<< orphan*/ * PyArray_malloc (int) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static NpyAuxData *_strided_datetime_cast_data_clone(NpyAuxData *data)
{
    _strided_datetime_cast_data *newdata =
            (_strided_datetime_cast_data *)PyArray_malloc(
                                        sizeof(_strided_datetime_cast_data));
    if (newdata == NULL) {
        return NULL;
    }

    memcpy(newdata, data, sizeof(_strided_datetime_cast_data));
    if (newdata->tmp_buffer != NULL) {
        newdata->tmp_buffer = PyArray_malloc(newdata->src_itemsize + 1);
        if (newdata->tmp_buffer == NULL) {
            PyArray_free(newdata);
            return NULL;
        }
    }

    return (NpyAuxData *)newdata;
}