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
typedef  scalar_t__ uint8_t ;
struct TYPE_2__ {scalar_t__ val; int /*<<< orphan*/  sat; int /*<<< orphan*/  hue; } ;

/* Variables and functions */
 scalar_t__ RGBLIGHT_VAL_STEP ; 
 TYPE_1__ rgblight_config ; 
 int /*<<< orphan*/  rgblight_sethsv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

void rgblight_decrease_val(void) {
  uint8_t val;
  if (rgblight_config.val - RGBLIGHT_VAL_STEP < 0) {
    val = 0;
  } else {
    val = rgblight_config.val - RGBLIGHT_VAL_STEP;
  }
  rgblight_sethsv(rgblight_config.hue, rgblight_config.sat, val);
}