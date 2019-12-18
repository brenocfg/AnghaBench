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
typedef  unsigned long uint8_t ;

/* Variables and functions */
 unsigned long _QWERTY ; 
 unsigned long eeconfig_read_default_layer () ; 
 int /*<<< orphan*/  rgblight_enable () ; 
 int /*<<< orphan*/  rgblight_mode (int) ; 

void matrix_init_user(void) {

  uint8_t default_layer = eeconfig_read_default_layer();

  rgblight_enable();

  if(true) {
   if (default_layer & (1UL << _QWERTY)) {
      //RGB_current_mode = rgblight_config.mode;
      rgblight_mode(11);
      }
 else {
      rgblight_mode (12);
      }

    /*else if (default_layer & (1UL << _DVORAK)) {
      rgblight_set_green;
    }
    //else if (default_layer & (1UL << _WORKMAN)) {
      rgblight_set_purple;
    }
    else {
      rgblight_set_teal;*/


  }


}