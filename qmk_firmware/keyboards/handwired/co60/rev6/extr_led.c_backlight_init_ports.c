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
struct TYPE_2__ {int /*<<< orphan*/  level; scalar_t__ breathing; scalar_t__ enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOB ; 
 int /*<<< orphan*/  PAL_MODE_ALTERNATE (int) ; 
 int /*<<< orphan*/  PWMD4 ; 
 int /*<<< orphan*/  backlight_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  breathing_enable () ; 
 TYPE_1__ kb_backlight_config ; 
 int /*<<< orphan*/  palSetPadMode (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwmCFG ; 
 int /*<<< orphan*/  pwmStart (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void backlight_init_ports(void) {
  palSetPadMode(GPIOB, 8, PAL_MODE_ALTERNATE(2));
  pwmStart(&PWMD4, &pwmCFG);
  if (kb_backlight_config.enable) {
    if (kb_backlight_config.breathing) {
      breathing_enable();
    } else {
      backlight_set(kb_backlight_config.level);
    }
  } else {
    backlight_set(0);
  }
}