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
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 scalar_t__ MP_START_TIME ; 
 scalar_t__ mp_raw_time_us () ; 
 scalar_t__ raw_time_offset ; 

int64_t mp_time_us(void)
{
    int64_t r = mp_raw_time_us() - raw_time_offset;
    if (r < MP_START_TIME)
        r = MP_START_TIME;
    return r;
}