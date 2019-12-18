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
struct TYPE_2__ {int /*<<< orphan*/ * flags; } ;

/* Variables and functions */
 int DRIVER_LED_TOTAL ; 
 int /*<<< orphan*/  HAS_FLAGS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LED_FLAG_MODIFIER ; 
#define  _ADJUST 130 
#define  _LOWER 129 
#define  _RAISE 128 
 int biton32 (int /*<<< orphan*/ ) ; 
 TYPE_1__ g_led_config ; 
 int /*<<< orphan*/  layer_state ; 
 int /*<<< orphan*/  rgb_matrix_set_color (int,int,int,int) ; 

void rgb_matrix_indicators_user(void) {
  #ifdef RGB_MATRIX_ENABLE
  switch (biton32(layer_state)) {
    case _RAISE:
      for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
        if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_MODIFIER)) {
          rgb_matrix_set_color(i, 0x6B, 0x00, 0x80);
        } else {
          rgb_matrix_set_color(i, 0x00, 0xFF, 0x00);
        }
      }
      break;

    case _LOWER:
      for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
        if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_MODIFIER)) {
          rgb_matrix_set_color(i, 0xFF, 0xA5, 0x00);
        } else {
          rgb_matrix_set_color(i, 0x00, 0x67, 0xC7);
        }
      }
      break;

    case _ADJUST:
      for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
        rgb_matrix_set_color(i, 0xFF, 0x99, 0x00);
      }
      rgb_matrix_set_color(1, 0xFF, 0x00, 0x00);
      break;

    default:
      break;
  }
  #endif
}