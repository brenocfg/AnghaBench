#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int num; int /*<<< orphan*/  base; } ;
typedef  TYPE_1__ PyArray_DatetimeMetaData ;

/* Variables and functions */
 int /*<<< orphan*/  NPY_FR_us ; 
 scalar_t__ compute_datetime_metadata_greatest_common_divisor (TYPE_1__*,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
delta_checker(PyArray_DatetimeMetaData *meta)
{
    PyArray_DatetimeMetaData tmp_meta;

    tmp_meta.base = NPY_FR_us;
    tmp_meta.num = 1;

    /* Combine it with 'meta' */
    if (compute_datetime_metadata_greatest_common_divisor(
            meta, &tmp_meta, meta, 0, 0) < 0) {
        return -1;
    }
    return 0;
}