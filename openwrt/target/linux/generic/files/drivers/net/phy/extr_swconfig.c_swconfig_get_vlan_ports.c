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
struct switch_val {scalar_t__ port_vlan; } ;
struct switch_dev {scalar_t__ vlans; TYPE_1__* ops; } ;
struct switch_attr {int dummy; } ;
struct TYPE_2__ {int (* get_vlan_ports ) (struct switch_dev*,struct switch_val*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int stub1 (struct switch_dev*,struct switch_val*) ; 

__attribute__((used)) static int
swconfig_get_vlan_ports(struct switch_dev *dev, const struct switch_attr *attr,
			struct switch_val *val)
{
	int ret;
	if (val->port_vlan >= dev->vlans)
		return -EINVAL;

	if (!dev->ops->get_vlan_ports)
		return -EOPNOTSUPP;

	ret = dev->ops->get_vlan_ports(dev, val);
	return ret;
}