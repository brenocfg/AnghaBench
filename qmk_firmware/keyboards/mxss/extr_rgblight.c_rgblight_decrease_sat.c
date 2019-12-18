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
struct TYPE_2__ {scalar_t__ sat; int /*<<< orphan*/  val; int /*<<< orphan*/  hue; } ;

/* Variables and functions */
 scalar_t__ RGBLIGHT_SAT_STEP ; 
 TYPE_1__ rgblight_config ; 
 int /*<<< orphan*/  rgblight_sethsv (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

void rgblight_decrease_sat(void) {
  uint8_t sat;
  if (rgblight_config.sat - RGBLIGHT_SAT_STEP < 0) {
    sat = 0;
  } else {
    sat = rgblight_config.sat - RGBLIGHT_SAT_STEP;
  }
  rgblight_sethsv(rgblight_config.hue, sat, rgblight_config.val);
}