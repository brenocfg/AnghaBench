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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  LED_TYPE ;

/* Variables and functions */
 scalar_t__ layer_state_cmp (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * led ; 
 int /*<<< orphan*/  rgblight_set () ; 
 int /*<<< orphan*/  setrgb (int,int,int,int /*<<< orphan*/ *) ; 

uint32_t layer_state_set_user(uint32_t state){
  #ifdef RGBLIGHT_ENABLE
    uint8_t led0r = 0; uint8_t led0g = 0; uint8_t led0b = 0;
    uint8_t led1r = 0; uint8_t led1g = 0; uint8_t led1b = 0;

    if (layer_state_cmp(state, 1)) {
      led0r = 255;
    }
    if (layer_state_cmp(state, 2)) {
      led0g = 255;
    }

    if (layer_state_cmp(state, 4)) {
      led1b = 255;
    }
    if (layer_state_cmp(state, 5)) {
      led1r = 255;
    }

    setrgb(led0r, led0g, led0b, (LED_TYPE *)&led[0]);
    setrgb(led1r, led1g, led1b, (LED_TYPE *)&led[1]);
    rgblight_set();
  #endif //RGBLIGHT_ENABLE
  return state;
}