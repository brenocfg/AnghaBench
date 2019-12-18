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
struct TYPE_2__ {scalar_t__ level; } ;

/* Variables and functions */
 int /*<<< orphan*/  BREATHING_HALT_ON ; 
 int /*<<< orphan*/  breathing_halt ; 
 int /*<<< orphan*/  breathing_interrupt_enable () ; 
 int /*<<< orphan*/  breathing_max () ; 
 int /*<<< orphan*/  breathing_min () ; 
 TYPE_1__ kb_backlight_config ; 

void breathing_pulse(void)
{
    if (kb_backlight_config.level == 0)
      breathing_min();
    else
      breathing_max();
    breathing_halt = BREATHING_HALT_ON;
    breathing_interrupt_enable();
}