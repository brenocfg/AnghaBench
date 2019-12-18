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

/* Variables and functions */
 int /*<<< orphan*/  Device_STATUSLED ; 
 int /*<<< orphan*/  cli () ; 
 int /*<<< orphan*/  sei () ; 
 int /*<<< orphan*/  send_color (int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show () ; 

void indicator_leds_set(bool leds[8]) {
  cli();
  send_color(leds[1] ? 255 : 0, leds[2] ? 255 : 0, leds[0] ? 255 : 0, Device_STATUSLED);
  send_color(leds[4] ? 255 : 0, leds[5] ? 255 : 0, leds[3] ? 255 : 0, Device_STATUSLED);
  send_color(leds[6] ? 255 : 0, leds[7] ? 255 : 0, 0, Device_STATUSLED);
  sei();
  show();
}