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
 size_t RGBLED_NUM ; 
 int /*<<< orphan*/  SET_LED_RGB (size_t const,size_t const,size_t const,size_t const,size_t) ; 
 size_t** _LC ; 
 size_t _VL ; 
 int /*<<< orphan*/  is_first_run () ; 
 size_t led_dim ; 

bool set_layer_led(uint8_t lyr) {
  static uint8_t p_lyr = 0; // Previous layer.
  static uint8_t p_dim = 0; // Previous dim.

  if (p_lyr == lyr && p_dim == led_dim && !is_first_run()) {
    return false;
  }

  p_lyr = lyr;
  p_dim = led_dim;
  const uint8_t r = _LC[lyr][0];
  const uint8_t g = _LC[lyr][1];
  const uint8_t b = _LC[lyr][2];
  const uint8_t d = (p_lyr == _VL && p_dim < 1) ? 1 : p_dim;

  for (uint8_t i = 0; i < RGBLED_NUM; i++) {
    SET_LED_RGB(r, g, b, d, i);
  }

  return true;
}