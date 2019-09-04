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
typedef  scalar_t__ npy_datetime ;

/* Variables and functions */

__attribute__((used)) static npy_datetime *
find_earliest_holiday_after(npy_datetime date,
            npy_datetime *holidays_begin, npy_datetime *holidays_end)
{
    npy_datetime *trial;

    /* Simple binary search */
    while (holidays_begin < holidays_end) {
        trial = holidays_begin + (holidays_end - holidays_begin) / 2;

        if (date < *trial) {
            holidays_end = trial;
        }
        else if (date > *trial) {
            holidays_begin = trial + 1;
        }
        else {
            return trial + 1;
        }
    }

    return holidays_begin;
}