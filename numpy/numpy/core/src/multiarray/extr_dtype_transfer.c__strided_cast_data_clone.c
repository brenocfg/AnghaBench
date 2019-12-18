#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  aop; int /*<<< orphan*/  aip; } ;
typedef  TYPE_1__ _strided_cast_data ;
typedef  int /*<<< orphan*/  NpyAuxData ;

/* Variables and functions */
 scalar_t__ PyArray_malloc (int) ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static NpyAuxData *_strided_cast_data_clone(NpyAuxData *data)
{
    _strided_cast_data *newdata =
            (_strided_cast_data *)PyArray_malloc(sizeof(_strided_cast_data));
    if (newdata == NULL) {
        return NULL;
    }

    memcpy(newdata, data, sizeof(_strided_cast_data));
    Py_INCREF(newdata->aip);
    Py_INCREF(newdata->aop);

    return (NpyAuxData *)newdata;
}