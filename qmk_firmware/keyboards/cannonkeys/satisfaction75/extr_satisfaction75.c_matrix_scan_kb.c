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
typedef  scalar_t__ uint16_t ;
struct TYPE_3__ {int millisecond; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISPLAYOFF ; 
 scalar_t__ OLED_OFF ; 
 int /*<<< orphan*/  RTCD1 ; 
 scalar_t__ ScreenOffInterval ; 
 int /*<<< orphan*/  draw_ui () ; 
 int /*<<< orphan*/  last_flush ; 
 scalar_t__ last_minute ; 
 TYPE_1__ last_timespec ; 
 scalar_t__ oled_mode ; 
 int oled_sleeping ; 
 int queue_for_send ; 
 int /*<<< orphan*/  read_host_led_state () ; 
 int /*<<< orphan*/  rtcGetTime (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  send_command (int /*<<< orphan*/ ) ; 
 scalar_t__ timer_elapsed (int /*<<< orphan*/ ) ; 

void matrix_scan_kb(void) {
  rtcGetTime(&RTCD1, &last_timespec);
  uint16_t minutes_since_midnight = last_timespec.millisecond / 1000 / 60;

  if (minutes_since_midnight != last_minute){
    last_minute = minutes_since_midnight;
    if(!oled_sleeping){
      queue_for_send = true;
    }
  }
#ifdef QWIIC_MICRO_OLED_ENABLE
  if (queue_for_send && oled_mode != OLED_OFF) {
    oled_sleeping = false;
    read_host_led_state();
    draw_ui();
    queue_for_send = false;
  }
  if (timer_elapsed(last_flush) > ScreenOffInterval && !oled_sleeping) {
    send_command(DISPLAYOFF);      /* 0xAE */
    oled_sleeping = true;
  }
#endif
}