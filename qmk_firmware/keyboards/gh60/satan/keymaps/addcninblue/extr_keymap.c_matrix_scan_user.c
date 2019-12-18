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
#define  _DEFAULT 132 
#define  _FN 131 
#define  _VIM 130 
#define  _VIM_CONTROL 129 
#define  _VIM_SHIFT 128 
 int /*<<< orphan*/  backlight_set (int) ; 
 int biton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_state ; 
 int old_layer ; 

void matrix_scan_user(void) {
  uint8_t layer = biton32(layer_state);

  if (old_layer != layer) {
    switch (layer) {
      case _DEFAULT:
      case _FN:
        backlight_set(1);
      break;
      case _VIM:
      case _VIM_SHIFT:
      case _VIM_CONTROL:
        backlight_set(4);
      break;
    }
    old_layer = layer;
  }
}