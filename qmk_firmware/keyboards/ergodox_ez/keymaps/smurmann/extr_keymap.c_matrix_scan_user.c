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
typedef  int uint8_t ;
struct TYPE_2__ {int mods; } ;

/* Variables and functions */
 int /*<<< orphan*/  KC_LALT ; 
 int /*<<< orphan*/  KC_LCTRL ; 
 int /*<<< orphan*/  KC_LSFT ; 
 int /*<<< orphan*/  LED_BRIGHTNESS_HI ; 
 int /*<<< orphan*/  LED_BRIGHTNESS_LO ; 
 int MOD_BIT (int /*<<< orphan*/ ) ; 
 int biton32 (int /*<<< orphan*/ ) ; 
 scalar_t__ capsOn ; 
 int /*<<< orphan*/  ergodox_right_led_1_off () ; 
 int /*<<< orphan*/  ergodox_right_led_1_on () ; 
 int /*<<< orphan*/  ergodox_right_led_1_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ergodox_right_led_2_off () ; 
 int /*<<< orphan*/  ergodox_right_led_2_on () ; 
 int /*<<< orphan*/  ergodox_right_led_2_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ergodox_right_led_3_off () ; 
 int /*<<< orphan*/  ergodox_right_led_3_on () ; 
 int /*<<< orphan*/  ergodox_right_led_3_set (int /*<<< orphan*/ ) ; 
 TYPE_1__* keyboard_report ; 
 int /*<<< orphan*/  layer_state ; 

void matrix_scan_user(void) {
   uint8_t layer = biton32(layer_state);

   if(layer == 1)
   {
      ergodox_right_led_2_on();
      ergodox_right_led_3_on();

      ergodox_right_led_2_set (LED_BRIGHTNESS_HI);
      ergodox_right_led_3_set (LED_BRIGHTNESS_HI);
   }

   if(capsOn)
   {
      ergodox_right_led_1_set (LED_BRIGHTNESS_HI);
      ergodox_right_led_1_on ();
   }

  if(keyboard_report->mods & MOD_BIT(KC_LSFT))
  { 
      ergodox_right_led_1_set (LED_BRIGHTNESS_HI);
      ergodox_right_led_1_on ();
  } else {
      ergodox_right_led_1_set (LED_BRIGHTNESS_LO);

      if(!capsOn)
      {
        ergodox_right_led_1_off ();
      }
  }

  if(keyboard_report->mods & MOD_BIT(KC_LALT))
  {
      ergodox_right_led_2_set (LED_BRIGHTNESS_HI);
      ergodox_right_led_2_on ();
  } else {
      ergodox_right_led_2_set (LED_BRIGHTNESS_LO);
     if(layer != 1)
     {
       ergodox_right_led_2_off ();
     }
  }

  if(keyboard_report->mods & MOD_BIT(KC_LCTRL))
  { 
      ergodox_right_led_3_set (LED_BRIGHTNESS_HI);
      ergodox_right_led_3_on ();
  } else {
      ergodox_right_led_3_set (LED_BRIGHTNESS_LO);
     if(layer != 1)
     {
       ergodox_right_led_3_off ();
     }
  }
}