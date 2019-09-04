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
struct TYPE_3__ {int tm_year; int tm_mon; int tm_mday; int tm_hour; int tm_min; int tm_sec; } ;
typedef  TYPE_1__ timeutils_struct_time_t ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  pyb_rtc_get_seconds () ; 
 int /*<<< orphan*/  timeutils_seconds_since_2000_to_struct_time (int /*<<< orphan*/ ,TYPE_1__*) ; 

DWORD get_fattime(void) {
    timeutils_struct_time_t tm;
    timeutils_seconds_since_2000_to_struct_time(pyb_rtc_get_seconds(), &tm);

    return ((tm.tm_year - 1980) << 25) | ((tm.tm_mon) << 21)  |
            ((tm.tm_mday) << 16)       | ((tm.tm_hour) << 11) |
            ((tm.tm_min) << 5)         | (tm.tm_sec >> 1);
}