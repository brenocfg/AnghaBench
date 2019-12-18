#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  day; int /*<<< orphan*/  month; int /*<<< orphan*/  year; } ;

/* Variables and functions */
 scalar_t__ ENC_MODE_CLOCK_SET ; 
 int /*<<< orphan*/  day_config ; 
 scalar_t__ encoder_mode ; 
 int hour_config ; 
 int last_minute ; 
 TYPE_1__ last_timespec ; 
 int minute_config ; 
 int /*<<< orphan*/  month_config ; 
 scalar_t__ time_config_idx ; 
 int /*<<< orphan*/  year_config ; 

void post_encoder_mode_change(){
  if(encoder_mode == ENC_MODE_CLOCK_SET){
    hour_config = (last_minute / 60);
    minute_config = last_minute % 60;
    year_config = last_timespec.year;
    month_config = last_timespec.month;
    day_config = last_timespec.day;
    time_config_idx = 0;
  }
}