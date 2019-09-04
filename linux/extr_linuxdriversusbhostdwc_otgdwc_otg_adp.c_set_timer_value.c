#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_4__ {int* probe_timer_values; } ;
struct TYPE_5__ {TYPE_1__ adp; } ;
typedef  TYPE_2__ dwc_otg_core_if_t ;

/* Variables and functions */

__attribute__((used)) static uint32_t set_timer_value(dwc_otg_core_if_t * core_if, uint32_t val)
{
	if (core_if->adp.probe_timer_values[0] == -1) {
		core_if->adp.probe_timer_values[0] = val;
		core_if->adp.probe_timer_values[1] = -1;
		return 1;
	} else {
		core_if->adp.probe_timer_values[1] =
		    core_if->adp.probe_timer_values[0];
		core_if->adp.probe_timer_values[0] = val;
		return 0;
	}
}