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
struct TYPE_2__ {int mode; } ;

/* Variables and functions */
 int RGB_INIT ; 
 int RGB_current_mode ; 
 int TOG_STATUS ; 
#define  _LOWER 130 
#define  _NAV 129 
#define  _QWERTY 128 
 int biton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_state ; 
 TYPE_1__ rgblight_config ; 
 int /*<<< orphan*/  rgblight_mode (int) ; 

void matrix_scan_user(void) {
   uint8_t layer = biton32(layer_state);
   switch (layer) {
     case _NAV:
         if (RGB_INIT) {} else {
           RGB_current_mode = rgblight_config.mode;
           RGB_INIT = true;
         }
         if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
         } else {
           TOG_STATUS = !TOG_STATUS;
           rgblight_mode(29);
         }
         break;
     case _LOWER:
         if (RGB_INIT) {} else {
           RGB_current_mode = rgblight_config.mode;
           RGB_INIT = true;
         }
         if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
         } else {
           TOG_STATUS = !TOG_STATUS;
           rgblight_mode(29);
         }
         break;
     case _QWERTY:
         if (RGB_INIT) {} else {
           RGB_current_mode = rgblight_config.mode;
           RGB_INIT = true;
         }
         rgblight_mode(RGB_current_mode);   // revert RGB to initial mode prior to RGB mode change
         TOG_STATUS = false;
         break;
   }
 }