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
typedef  size_t uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  Device_PCBRGB ; 
 size_t RGBLED_NUM ; 
 int /*<<< orphan*/  cli () ; 
 int /*<<< orphan*/  sei () ; 
 int /*<<< orphan*/  send_color (size_t,size_t,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show () ; 

void backlight_set_rgb(uint8_t cfg[RGBLED_NUM][3])
{
  cli();
  for(uint8_t i = 0; i < RGBLED_NUM; ++i) {
    send_color(cfg[i][0], cfg[i][1], cfg[i][2], Device_PCBRGB);
  }
  sei();
  show();
}