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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  eeconfig_read_default_layer () ; 
 int /*<<< orphan*/  rgblight_enable () ; 
 int /*<<< orphan*/  update_rgblight (int /*<<< orphan*/ ) ; 

void matrix_init_user(void) {
  #ifdef RGBLIGHT_ENABLE
  rgblight_enable();
  uint8_t default_layer = eeconfig_read_default_layer();
  update_rgblight(default_layer);
  #endif
}