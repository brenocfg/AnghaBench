#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  _strided_zero_pad_data ;
typedef  int /*<<< orphan*/  NpyAuxData ;

/* Variables and functions */
 scalar_t__ PyArray_malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static NpyAuxData *_strided_zero_pad_data_clone(NpyAuxData *data)
{
    _strided_zero_pad_data *newdata =
            (_strided_zero_pad_data *)PyArray_malloc(
                                    sizeof(_strided_zero_pad_data));
    if (newdata == NULL) {
        return NULL;
    }

    memcpy(newdata, data, sizeof(_strided_zero_pad_data));

    return (NpyAuxData *)newdata;
}