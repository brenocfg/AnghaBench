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

/* Variables and functions */
 int biton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_state ; 
 int /*<<< orphan*/  rgblight_mode (int) ; 
 int /*<<< orphan*/  rgblight_setrgb (int,int,int) ; 

void matrix_scan_user(void) {
  static uint8_t old_layer = 255;
  uint8_t new_layer = biton32(layer_state);

  if (old_layer != new_layer) {
    switch (new_layer) {
    case 0:
      rgblight_mode(1);
      rgblight_setrgb(0xFF, 0xFF, 0xFF);
      break;
    case 1:
      rgblight_mode(18);
      rgblight_setrgb(0x00, 0xFF, 0xFF);
      break;
    }

    old_layer = new_layer;
  }
}