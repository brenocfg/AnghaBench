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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int tm_year; scalar_t__ tm_sec; scalar_t__ tm_min; scalar_t__ tm_hour; scalar_t__ tm_mday; scalar_t__ tm_mon; } ;
typedef  TYPE_1__ timeutils_struct_time_t ;
typedef  int DWORD ;

/* Variables and functions */
 int pyb_rtc_get_us_since_2000 () ; 
 int /*<<< orphan*/  timeutils_seconds_since_2000_to_struct_time (int /*<<< orphan*/ ,TYPE_1__*) ; 

DWORD get_fattime(void) {

    // TODO: Optimize division (there's no HW division support on ESP8266,
    // so it's expensive).
    uint32_t secs = (uint32_t)(pyb_rtc_get_us_since_2000() / 1000000);

    timeutils_struct_time_t tm;
    timeutils_seconds_since_2000_to_struct_time(secs, &tm);

    return (((DWORD)(tm.tm_year - 1980) << 25) | ((DWORD)tm.tm_mon << 21) | ((DWORD)tm.tm_mday << 16) |
           ((DWORD)tm.tm_hour << 11) | ((DWORD)tm.tm_min << 5) | ((DWORD)tm.tm_sec >> 1));
}