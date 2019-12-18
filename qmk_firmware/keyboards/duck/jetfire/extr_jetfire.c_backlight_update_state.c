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
 int STATE_LED_CAPS_LOCK ; 
 int STATE_LED_LAYER_0 ; 
 int STATE_LED_LAYER_1 ; 
 int STATE_LED_LAYER_2 ; 
 int STATE_LED_LAYER_3 ; 
 int STATE_LED_LAYER_4 ; 
 int STATE_LED_NUM_LOCK ; 
 int STATE_LED_SCROLL_LOCK ; 
 int backlight_state_led ; 
 int /*<<< orphan*/  cli () ; 
 int /*<<< orphan*/  sei () ; 
 int /*<<< orphan*/  send_color (int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show () ; 

void backlight_update_state()
{
  cli();
  send_color(backlight_state_led & (1<<STATE_LED_SCROLL_LOCK) ? 255 : 0,
             backlight_state_led & (1<<STATE_LED_CAPS_LOCK) ? 255 : 0,
             backlight_state_led & (1<<STATE_LED_NUM_LOCK) ? 255 : 0,
             Device_STATUSLED);
  send_color(backlight_state_led & (1<<STATE_LED_LAYER_1) ? 255 : 0,
             backlight_state_led & (1<<STATE_LED_LAYER_2) ? 255 : 0,
             backlight_state_led & (1<<STATE_LED_LAYER_0) ? 255 : 0,
             Device_STATUSLED);
  send_color(backlight_state_led & (1<<STATE_LED_LAYER_4) ? 255 : 0,
             backlight_state_led & (1<<STATE_LED_LAYER_3) ? 255 : 0,
             0,
             Device_STATUSLED);
  sei();
  show();
}