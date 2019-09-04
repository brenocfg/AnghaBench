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
struct devlink_port_attrs {int flavour; int port_number; int split_subport_number; int /*<<< orphan*/  split; int /*<<< orphan*/  set; } ;
struct devlink_port {struct devlink_port_attrs attrs; } ;

/* Variables and functions */
#define  DEVLINK_PORT_FLAVOUR_CPU 130 
#define  DEVLINK_PORT_FLAVOUR_DSA 129 
#define  DEVLINK_PORT_FLAVOUR_PHYSICAL 128 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int snprintf (char*,size_t,char*,int,...) ; 

int devlink_port_get_phys_port_name(struct devlink_port *devlink_port,
				    char *name, size_t len)
{
	struct devlink_port_attrs *attrs = &devlink_port->attrs;
	int n = 0;

	if (!attrs->set)
		return -EOPNOTSUPP;

	switch (attrs->flavour) {
	case DEVLINK_PORT_FLAVOUR_PHYSICAL:
		if (!attrs->split)
			n = snprintf(name, len, "p%u", attrs->port_number);
		else
			n = snprintf(name, len, "p%us%u", attrs->port_number,
				     attrs->split_subport_number);
		break;
	case DEVLINK_PORT_FLAVOUR_CPU:
	case DEVLINK_PORT_FLAVOUR_DSA:
		/* As CPU and DSA ports do not have a netdevice associated
		 * case should not ever happen.
		 */
		WARN_ON(1);
		return -EINVAL;
	}

	if (n >= len)
		return -EINVAL;

	return 0;
}