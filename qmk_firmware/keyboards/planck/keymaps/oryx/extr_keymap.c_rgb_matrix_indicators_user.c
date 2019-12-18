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
struct TYPE_2__ {scalar_t__ disable_layer_led; } ;

/* Variables and functions */
 int /*<<< orphan*/  LED_FLAG_NONE ; 
 int biton32 (int /*<<< orphan*/ ) ; 
 scalar_t__ g_suspend_state ; 
 TYPE_1__ keyboard_config ; 
 int /*<<< orphan*/  layer_state ; 
 int /*<<< orphan*/  rgb_matrix_get_flags () ; 
 int /*<<< orphan*/  rgb_matrix_set_color_all (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_layer_color (int) ; 

void rgb_matrix_indicators_user(void) {
  if (g_suspend_state || keyboard_config.disable_layer_led) { return; }
  switch (biton32(layer_state)) {
    case 0:
      set_layer_color(0);
      break;
    case 3:
      set_layer_color(1);
      break;
    case 4:
      set_layer_color(2);
      break;
    case 6:
      set_layer_color(3);
      break;
   default:
    if (rgb_matrix_get_flags() == LED_FLAG_NONE)
      rgb_matrix_set_color_all(0, 0, 0);
    break;
  }
}