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
struct TYPE_2__ {int /*<<< orphan*/  i; } ;
struct switch_val {int port_vlan; TYPE_1__ value; } ;
struct switch_dev {int ports; } ;
struct switch_attr {int dummy; } ;

/* Variables and functions */
 scalar_t__ ar8327_sw_get_port_igmp_snooping (struct switch_dev*,struct switch_attr const*,struct switch_val*) ; 

int
ar8327_sw_get_igmp_snooping(struct switch_dev *dev,
			    const struct switch_attr *attr,
			    struct switch_val *val)
{
	int port;

	for (port = 0; port < dev->ports; port++) {
		val->port_vlan = port;
		if (ar8327_sw_get_port_igmp_snooping(dev, attr, val) ||
		    !val->value.i)
			break;
	}

	return 0;
}