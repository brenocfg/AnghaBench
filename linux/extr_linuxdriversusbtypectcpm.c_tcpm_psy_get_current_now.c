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
union power_supply_propval {int intval; } ;
struct tcpm_port {int current_limit; } ;

/* Variables and functions */

__attribute__((used)) static int tcpm_psy_get_current_now(struct tcpm_port *port,
				    union power_supply_propval *val)
{
	val->intval = port->current_limit * 1000;

	return 0;
}