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
struct tcpm_port {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  TCPM_PSY_FIXED_ONLINE 129 
#define  TCPM_PSY_PROG_ONLINE 128 
 int tcpm_pps_activate (struct tcpm_port*,int) ; 

__attribute__((used)) static int tcpm_psy_set_online(struct tcpm_port *port,
			       const union power_supply_propval *val)
{
	int ret;

	switch (val->intval) {
	case TCPM_PSY_FIXED_ONLINE:
		ret = tcpm_pps_activate(port, false);
		break;
	case TCPM_PSY_PROG_ONLINE:
		ret = tcpm_pps_activate(port, true);
		break;
	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}