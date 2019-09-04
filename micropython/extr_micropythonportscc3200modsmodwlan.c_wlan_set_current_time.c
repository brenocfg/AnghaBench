#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  tm_sec; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_year; int /*<<< orphan*/  tm_mon; int /*<<< orphan*/  tm_mday; } ;
typedef  TYPE_1__ timeutils_struct_time_t ;
typedef  int /*<<< orphan*/  _u8 ;
struct TYPE_5__ {int /*<<< orphan*/  sl_tm_sec; int /*<<< orphan*/  sl_tm_min; int /*<<< orphan*/  sl_tm_hour; int /*<<< orphan*/  sl_tm_year; int /*<<< orphan*/  sl_tm_mon; int /*<<< orphan*/  sl_tm_day; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ SlDateTime_t ;

/* Variables and functions */
 int /*<<< orphan*/  SL_DEVICE_GENERAL_CONFIGURATION ; 
 int /*<<< orphan*/  SL_DEVICE_GENERAL_CONFIGURATION_DATE_TIME ; 
 int /*<<< orphan*/  sl_DevSet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timeutils_seconds_since_2000_to_struct_time (int /*<<< orphan*/ ,TYPE_1__*) ; 

void wlan_set_current_time (uint32_t seconds_since_2000) {
    timeutils_struct_time_t tm;
    timeutils_seconds_since_2000_to_struct_time(seconds_since_2000, &tm);

    SlDateTime_t sl_datetime = {0};
    sl_datetime.sl_tm_day  = tm.tm_mday;
    sl_datetime.sl_tm_mon  = tm.tm_mon;
    sl_datetime.sl_tm_year = tm.tm_year;
    sl_datetime.sl_tm_hour = tm.tm_hour;
    sl_datetime.sl_tm_min  = tm.tm_min;
    sl_datetime.sl_tm_sec  = tm.tm_sec;
    sl_DevSet(SL_DEVICE_GENERAL_CONFIGURATION, SL_DEVICE_GENERAL_CONFIGURATION_DATE_TIME, sizeof(SlDateTime_t), (_u8 *)(&sl_datetime));
}