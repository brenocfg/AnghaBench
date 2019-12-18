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
typedef  int msg_t ;

/* Variables and functions */
 int ALL ; 
 int DISPLAY_PAGE ; 
 int GAME ; 
#define  MODE_FLASH 130 
#define  MODE_PAGE 129 
#define  MODE_SINGLE 128 
 int SET_FULL_ROW ; 
 int /*<<< orphan*/  TIME_IMMEDIATE ; 
 scalar_t__ backlight_status_global ; 
 int biton32 (scalar_t__) ; 
 int /*<<< orphan*/  chMBPost (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chThdSleepMilliseconds (int) ; 
 scalar_t__ layer_state ; 
 scalar_t__ led_layer_state ; 
 int /*<<< orphan*/  led_mailbox ; 
 int led_mode_global ; 
 int max_pages ; 

void matrix_scan_user(void) {
  uint8_t page;
  uint8_t led_pin_byte;
  msg_t msg;

  if (backlight_status_global == 0) {//backlight is off, skip the rest
    return;
  }

  if (led_layer_state != layer_state && led_mode_global != GAME && led_mode_global != ALL) {
    //check mode
    //Turn on layer indicator or page depending on mode
    switch(led_mode_global) {
      case MODE_FLASH: //flash preset page leds then single indicator
        page = biton32(layer_state) > max_pages ? 7 : biton32(layer_state);
        msg=(page << 8) | DISPLAY_PAGE;
        chMBPost(&led_mailbox, msg, TIME_IMMEDIATE);
        chThdSleepMilliseconds(500);
        //flow to display single layer leds

      case MODE_SINGLE: //light layer indicators for all active layers
        led_pin_byte = layer_state & 0xFF;
        msg=(7 << 8) | DISPLAY_PAGE;
        chMBPost(&led_mailbox, msg, TIME_IMMEDIATE);
        msg=(1 << 16) | (led_pin_byte << 8) | SET_FULL_ROW;
        chMBPost(&led_mailbox, msg, TIME_IMMEDIATE);
        break;

      case MODE_PAGE: //display pre-defined led page
        page = biton32(layer_state) > max_pages ? 7 : biton32(layer_state);
        msg=(page << 8) | DISPLAY_PAGE;
        chMBPost(&led_mailbox, msg, TIME_IMMEDIATE);
        break;
      }
  led_layer_state = layer_state;
  }
}