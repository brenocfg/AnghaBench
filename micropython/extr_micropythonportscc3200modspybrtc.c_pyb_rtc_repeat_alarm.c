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
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_4__ {int alarm_time_s; scalar_t__ alarm_time_ms; scalar_t__ alarm_ms; scalar_t__ repeat; } ;
typedef  TYPE_1__ pyb_rtc_obj_t ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ PYB_RTC_MIN_ALARM_TIME_MS ; 
 int /*<<< orphan*/  pyb_rtc_calc_future_time (scalar_t__,int*,scalar_t__*) ; 
 int /*<<< orphan*/  pyb_rtc_get_time (int*,scalar_t__*) ; 
 int /*<<< orphan*/  pyb_rtc_set_alarm (TYPE_1__*,int,scalar_t__) ; 

void pyb_rtc_repeat_alarm (pyb_rtc_obj_t *self) {
    if (self->repeat) {
        uint32_t f_seconds, c_seconds;
        uint16_t f_mseconds, c_mseconds;

        pyb_rtc_get_time(&c_seconds, &c_mseconds);

        // substract the time elapsed between waking up and setting up the alarm again
        int32_t wake_ms = ((c_seconds * 1000) + c_mseconds) - ((self->alarm_time_s * 1000) + self->alarm_time_ms);
        int32_t next_alarm = self->alarm_ms - wake_ms;
        next_alarm = next_alarm > 0 ? next_alarm : PYB_RTC_MIN_ALARM_TIME_MS;
        pyb_rtc_calc_future_time (next_alarm, &f_seconds, &f_mseconds);

        // now configure the alarm
        pyb_rtc_set_alarm (self, f_seconds, f_mseconds);
    }
}