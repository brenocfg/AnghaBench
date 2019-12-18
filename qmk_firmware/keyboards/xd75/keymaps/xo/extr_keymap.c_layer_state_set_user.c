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
typedef  int /*<<< orphan*/  layer_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  BASE_COLOR ; 
 int /*<<< orphan*/  RGB_AZURE ; 
 int /*<<< orphan*/  RGB_PURPLE ; 
 int get_highest_layer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgblight_setrgb (int /*<<< orphan*/ ) ; 

layer_state_t layer_state_set_user(layer_state_t state) {
  switch (get_highest_layer(state)) {
    case 0:
      rgblight_setrgb(BASE_COLOR);
      break;
    case 1:
      rgblight_setrgb(RGB_AZURE);
      break;
    case 2:
      rgblight_setrgb(RGB_PURPLE);
      break;
    }
  return state;
}