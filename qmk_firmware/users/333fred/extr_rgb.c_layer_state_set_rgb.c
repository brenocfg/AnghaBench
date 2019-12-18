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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
#define  BASE 131 
#define  GAME 130 
#define  SYMB 129 
#define  VIM 128 
 int biton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgblight_sethsv_noeeprom (int,int,int) ; 

void layer_state_set_rgb(uint32_t state) {
  switch (biton32(state)) {
    case BASE:
      // purple
      rgblight_sethsv_noeeprom(210, 255, 20);
      break;
    case SYMB:
      // blue
      rgblight_sethsv_noeeprom(191, 255, 20);
      break;
    case VIM:
      // green
      rgblight_sethsv_noeeprom(85, 255, 20);
      break;
    case GAME:
      // red
      rgblight_sethsv_noeeprom(0, 255, 20);
      break;
  }
}