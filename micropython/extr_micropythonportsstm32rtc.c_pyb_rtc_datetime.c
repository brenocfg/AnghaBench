#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mp_obj_t ;
struct TYPE_8__ {void* WeekDay; void* Date; void* Month; void* Year; } ;
struct TYPE_7__ {int /*<<< orphan*/  StoreOperation; int /*<<< orphan*/  DayLightSaving; int /*<<< orphan*/  TimeFormat; void* Seconds; void* Minutes; void* Hours; int /*<<< orphan*/  SubSeconds; } ;
typedef  TYPE_1__ RTC_TimeTypeDef ;
typedef  TYPE_2__ RTC_DateTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  HAL_RTC_GetDate (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HAL_RTC_GetTime (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HAL_RTC_SetDate (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HAL_RTC_SetTime (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTCHandle ; 
 int /*<<< orphan*/  RTC_DAYLIGHTSAVING_NONE ; 
 int /*<<< orphan*/  RTC_FORMAT_BIN ; 
 int /*<<< orphan*/  RTC_HOURFORMAT12_AM ; 
 int /*<<< orphan*/  RTC_STOREOPERATION_SET ; 
 int /*<<< orphan*/  mp_const_none ; 
 int /*<<< orphan*/  mp_obj_get_array_fixed_n (int /*<<< orphan*/  const,int,int /*<<< orphan*/ **) ; 
 void* mp_obj_get_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_obj_new_int (void*) ; 
 int /*<<< orphan*/  mp_obj_new_tuple (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtc_init_finalise () ; 
 void* rtc_subsec_to_us (int /*<<< orphan*/ ) ; 

mp_obj_t pyb_rtc_datetime(size_t n_args, const mp_obj_t *args) {
    rtc_init_finalise();
    if (n_args == 1) {
        // get date and time
        // note: need to call get time then get date to correctly access the registers
        RTC_DateTypeDef date;
        RTC_TimeTypeDef time;
        HAL_RTC_GetTime(&RTCHandle, &time, RTC_FORMAT_BIN);
        HAL_RTC_GetDate(&RTCHandle, &date, RTC_FORMAT_BIN);
        mp_obj_t tuple[8] = {
            mp_obj_new_int(2000 + date.Year),
            mp_obj_new_int(date.Month),
            mp_obj_new_int(date.Date),
            mp_obj_new_int(date.WeekDay),
            mp_obj_new_int(time.Hours),
            mp_obj_new_int(time.Minutes),
            mp_obj_new_int(time.Seconds),
            mp_obj_new_int(rtc_subsec_to_us(time.SubSeconds)),
        };
        return mp_obj_new_tuple(8, tuple);
    } else {
        // set date and time
        mp_obj_t *items;
        mp_obj_get_array_fixed_n(args[1], 8, &items);

        RTC_DateTypeDef date;
        date.Year = mp_obj_get_int(items[0]) - 2000;
        date.Month = mp_obj_get_int(items[1]);
        date.Date = mp_obj_get_int(items[2]);
        date.WeekDay = mp_obj_get_int(items[3]);
        HAL_RTC_SetDate(&RTCHandle, &date, RTC_FORMAT_BIN);

        RTC_TimeTypeDef time;
        time.Hours = mp_obj_get_int(items[4]);
        time.Minutes = mp_obj_get_int(items[5]);
        time.Seconds = mp_obj_get_int(items[6]);
        time.TimeFormat = RTC_HOURFORMAT12_AM;
        time.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
        time.StoreOperation = RTC_STOREOPERATION_SET;
        HAL_RTC_SetTime(&RTCHandle, &time, RTC_FORMAT_BIN);

        return mp_const_none;
    }
}