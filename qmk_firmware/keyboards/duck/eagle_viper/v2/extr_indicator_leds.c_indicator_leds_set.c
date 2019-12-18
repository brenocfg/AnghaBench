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
typedef  int uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  Device_STATUSLED ; 
 int /*<<< orphan*/  cli () ; 
 int /*<<< orphan*/  sei () ; 
 int /*<<< orphan*/  send_value (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show () ; 

void indicator_leds_set(bool leds[8]) {
  uint8_t led_cnt;

  cli();
  for(led_cnt = 0; led_cnt < 8; led_cnt++)
    send_value(leds[led_cnt] ? 255 : 0, Device_STATUSLED);
  sei();
  show();
}