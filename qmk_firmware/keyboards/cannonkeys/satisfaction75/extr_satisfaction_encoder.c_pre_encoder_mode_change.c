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
struct TYPE_3__ {int millisecond; int /*<<< orphan*/  day; int /*<<< orphan*/  month; int /*<<< orphan*/  year; } ;
typedef  TYPE_1__ RTCDateTime ;

/* Variables and functions */
 scalar_t__ ENC_MODE_BACKLIGHT ; 
 scalar_t__ ENC_MODE_CLOCK_SET ; 
 int /*<<< orphan*/  RTCD1 ; 
 int /*<<< orphan*/  day_config ; 
 scalar_t__ encoder_mode ; 
 int hour_config ; 
 int minute_config ; 
 int /*<<< orphan*/  month_config ; 
 int /*<<< orphan*/  rtcSetTime (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  save_backlight_config_to_eeprom () ; 
 int /*<<< orphan*/  year_config ; 

void pre_encoder_mode_change(){
  if(encoder_mode == ENC_MODE_CLOCK_SET){
    RTCDateTime timespec;
    timespec.year = year_config;
    timespec.month = month_config;
    timespec.day = day_config;
    // timespec.dayofweek = last_timespec.dayofweek;
    // timespec.dstflag = last_timespec.dstflag;
    timespec.millisecond = (hour_config * 60 + minute_config) * 60 * 1000;
    rtcSetTime(&RTCD1, &timespec);
  } else if (encoder_mode == ENC_MODE_BACKLIGHT){
    save_backlight_config_to_eeprom();
  }
}