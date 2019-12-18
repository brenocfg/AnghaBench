#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct switch_port_link* link; } ;
struct switch_val {scalar_t__ port_vlan; TYPE_1__ value; } ;
struct switch_port_link {int dummy; } ;
struct switch_dev {scalar_t__ ports; TYPE_2__* ops; } ;
struct switch_attr {int dummy; } ;
struct TYPE_4__ {int (* get_port_link ) (struct switch_dev*,scalar_t__,struct switch_port_link*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  memset (struct switch_port_link*,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct switch_dev*,scalar_t__,struct switch_port_link*) ; 

__attribute__((used)) static int
swconfig_get_link(struct switch_dev *dev, const struct switch_attr *attr,
			struct switch_val *val)
{
	struct switch_port_link *link = val->value.link;

	if (val->port_vlan >= dev->ports)
		return -EINVAL;

	if (!dev->ops->get_port_link)
		return -EOPNOTSUPP;

	memset(link, 0, sizeof(*link));
	return dev->ops->get_port_link(dev, val->port_vlan, link);
}