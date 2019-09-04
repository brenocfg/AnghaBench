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
union power_supply_propval {int intval; } ;
struct TYPE_2__ {int max_curr; scalar_t__ active; } ;
struct tcpm_port {int current_limit; TYPE_1__ pps_data; } ;

/* Variables and functions */

__attribute__((used)) static int tcpm_psy_get_current_max(struct tcpm_port *port,
				    union power_supply_propval *val)
{
	if (port->pps_data.active)
		val->intval = port->pps_data.max_curr * 1000;
	else
		val->intval = port->current_limit * 1000;

	return 0;
}