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
typedef  float uint8_t ;
struct TYPE_4__ {float r; float g; float b; } ;
typedef  TYPE_1__ LED_TYPE ;

/* Variables and functions */
 TYPE_1__* led ; 
 scalar_t__ rgblight_get_val () ; 
 int /*<<< orphan*/  rgblight_set () ; 
 TYPE_1__* shadowed_led ; 
 scalar_t__ user_rgb_mode ; 

void rgbflag(uint8_t r, uint8_t g, uint8_t b) {
  float rgb_brightness = ((float)rgblight_get_val())/256;
  if(rgb_brightness == 0) rgb_brightness = 0.05;
  LED_TYPE *target_led = user_rgb_mode ? shadowed_led : led;
  target_led[0].r = (uint8_t)(r*rgb_brightness);
  target_led[0].g = (uint8_t)(g*rgb_brightness);
  target_led[0].b = (uint8_t)(b*rgb_brightness);
  rgblight_set(); // just to handle turning off if that's required
}