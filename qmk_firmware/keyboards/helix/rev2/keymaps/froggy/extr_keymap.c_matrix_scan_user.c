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
 scalar_t__ DELAY_TIME ; 
#define  L_BASE 132 
#define  L_FUNC 131 
#define  L_NUM 130 
#define  L_OPT 129 
#define  L_SYM 128 
 int /*<<< orphan*/  RGBAnimation ; 
 int /*<<< orphan*/  _BASE ; 
 int /*<<< orphan*/  _FUNC ; 
 int /*<<< orphan*/  _NUM ; 
 int /*<<< orphan*/  _OPT ; 
 int /*<<< orphan*/  _SYM ; 
 int /*<<< orphan*/  delay_key_pressed ; 
 scalar_t__ delay_key_stat ; 
 int /*<<< orphan*/  iota_gfx_task () ; 
 int /*<<< orphan*/  key_timer ; 
 int layer_state ; 
 int layer_state_old ; 
 int /*<<< orphan*/  led_ripple_effect (int,int,int) ; 
 int /*<<< orphan*/  register_delay_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgblight_setrgb (int,int,int) ; 
 scalar_t__ timer_elapsed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_delay_code () ; 

void matrix_scan_user(void) {
  #ifdef SSD1306OLED
    iota_gfx_task();  // this is what updates the display continuously
  #endif

  if(delay_key_stat && (timer_elapsed(key_timer) > DELAY_TIME)){
    register_delay_code(_BASE);
    if(!delay_key_pressed){
      unregister_delay_code();
    }
  }

  if(layer_state_old != layer_state){
    switch (layer_state) {
      case L_BASE:
        break;
      case L_OPT:
        register_delay_code(_OPT);
        break;
      case L_NUM:
        register_delay_code(_NUM);
        break;
      case L_SYM:
        register_delay_code(_SYM);
        break;
      case L_FUNC:
        register_delay_code(_FUNC);
        break;
    }
    layer_state_old = layer_state;
  }

  #ifdef RGBLIGHT_ENABLE
    if(!RGBAnimation){
      switch (layer_state) {
        case L_BASE:
          #ifdef RGBLED_BACK
            led_ripple_effect(0,112,127);
          #else
            rgblight_setrgb(0,112,127);
          #endif
          break;
        case L_OPT:
          #ifdef RGBLED_BACK
            led_ripple_effect(127,0,100);
          #else
            rgblight_setrgb(127,0,100);
          #endif
          break;
        case L_NUM:
          #ifdef RGBLED_BACK
            led_ripple_effect(127,23,0);
          #else
            rgblight_setrgb(127,23,0);
          #endif
          break;
        case L_SYM:
          #ifdef RGBLED_BACK
            led_ripple_effect(0,127,0);
          #else
            rgblight_setrgb(0,127,0);
          #endif
          break;
        case L_FUNC:
          #ifdef RGBLED_BACK
            led_ripple_effect(127,0,61);
          #else
            rgblight_setrgb(127,0,61);
          #endif
          break;
        }
    }
  #endif
}