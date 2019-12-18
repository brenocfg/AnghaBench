#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int msg_t ;
struct TYPE_4__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_5__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
#define  ACTION_LEDS_ALL 135 
#define  ACTION_LEDS_BACKLIGHT 134 
#define  ACTION_LEDS_BRIGHT 133 
#define  ACTION_LEDS_DIM 132 
#define  ACTION_LEDS_FLASH 131 
#define  ACTION_LEDS_GAME 130 
#define  ACTION_LEDS_PAGE 129 
#define  ACTION_LEDS_SINGLE 128 
 int /*<<< orphan*/  ALL ; 
 int DISPLAY_PAGE ; 
 int /*<<< orphan*/  GAME ; 
 int /*<<< orphan*/  MODE_FLASH ; 
 int /*<<< orphan*/  MODE_PAGE ; 
 int /*<<< orphan*/  MODE_SINGLE ; 
 int STEP_BRIGHTNESS ; 
 int /*<<< orphan*/  TIME_IMMEDIATE ; 
 int TOGGLE_ALL ; 
 int TOGGLE_BACKLIGHT ; 
 int backlight_status_global ; 
 int /*<<< orphan*/  chMBPost (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  led_mailbox ; 
 int /*<<< orphan*/  led_mode_global ; 

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
  msg_t msg;

  switch(id) {
    case ACTION_LEDS_ALL:
      if(record->event.pressed) {
        led_mode_global = led_mode_global == ALL ? MODE_SINGLE : ALL;
        msg=TOGGLE_ALL;
        chMBPost(&led_mailbox, msg, TIME_IMMEDIATE);
      }
      break;

    case ACTION_LEDS_BACKLIGHT:
      if(record->event.pressed) {
        backlight_status_global ^= 1;
        msg=(backlight_status_global << 8) | TOGGLE_BACKLIGHT;
        chMBPost(&led_mailbox, msg, TIME_IMMEDIATE);
      }
      break;

    case ACTION_LEDS_GAME:
      if(record->event.pressed) {
        led_mode_global = led_mode_global == GAME ? MODE_SINGLE : GAME;

        msg=(4 << 8) | DISPLAY_PAGE;
        chMBPost(&led_mailbox, msg, TIME_IMMEDIATE);
      }
      break;

    case ACTION_LEDS_BRIGHT:
      if(record->event.pressed) {
        msg=(1 << 8) | STEP_BRIGHTNESS;
        chMBPost(&led_mailbox, msg, TIME_IMMEDIATE);
      }
      break;

    case ACTION_LEDS_DIM:
      if(record->event.pressed) {
        msg=(0 << 8) | STEP_BRIGHTNESS;
        chMBPost(&led_mailbox, msg, TIME_IMMEDIATE);
      }
      break;

    //set led_mode for matrix_scan to toggle leds
    case ACTION_LEDS_SINGLE:
      led_mode_global = MODE_SINGLE;
      break;
    case ACTION_LEDS_PAGE:
      led_mode_global = MODE_PAGE;
      break;
    case ACTION_LEDS_FLASH:
      led_mode_global = MODE_FLASH;
      break;

  }
}