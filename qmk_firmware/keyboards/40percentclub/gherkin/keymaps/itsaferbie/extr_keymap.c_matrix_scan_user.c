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
#define  _AI 131 
#define  _PR 130 
#define  _PS 129 
#define  _XD 128 
 int biton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_state ; 
 int /*<<< orphan*/  rgblight_setrgb (int,int,int) ; 

void matrix_scan_user(void) {
  #ifdef RGBLIGHT_ENABLE

  static uint8_t old_layer = 255;
  uint8_t new_layer = biton32(layer_state);

  // Color of the Icons.
  if (old_layer != new_layer) {
    switch (new_layer) {
      case _PS:
        // #31C5F0
        rgblight_setrgb(49, 197, 240);
      break;
      case _AI:
        // #FF8011
        rgblight_setrgb(255, 128, 17);
      break;
      case _PR:
        // #E788FF
        rgblight_setrgb(231, 136, 255);
      break;
      case _XD:
        // #FF2BC2
        rgblight_setrgb(255, 43, 194);
      break;
    }
    old_layer = new_layer;
  }
  #endif
}