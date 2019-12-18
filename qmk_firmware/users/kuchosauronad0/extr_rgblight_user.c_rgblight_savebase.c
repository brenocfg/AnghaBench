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
struct TYPE_2__ {int /*<<< orphan*/  mode; int /*<<< orphan*/  val; int /*<<< orphan*/  sat; int /*<<< orphan*/  hue; } ;

/* Variables and functions */
 int /*<<< orphan*/  base_hue ; 
 int /*<<< orphan*/  base_mod ; 
 int /*<<< orphan*/  base_sat ; 
 int /*<<< orphan*/  base_val ; 
 TYPE_1__ rgblight_config ; 

void rgblight_savebase(void) {  // Save the current settings to ram
  base_hue = rgblight_config.hue;
  base_sat = rgblight_config.sat;
  base_val = rgblight_config.val;
  base_mod = rgblight_config.mode;
}