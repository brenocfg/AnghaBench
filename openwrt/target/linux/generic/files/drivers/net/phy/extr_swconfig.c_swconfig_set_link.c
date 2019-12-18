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
struct TYPE_4__ {int /*<<< orphan*/  link; } ;
struct switch_val {TYPE_2__ value; int /*<<< orphan*/  port_vlan; } ;
struct switch_dev {TYPE_1__* ops; } ;
struct switch_attr {int dummy; } ;
struct TYPE_3__ {int (* set_port_link ) (struct switch_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int stub1 (struct switch_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
swconfig_set_link(struct switch_dev *dev, const struct switch_attr *attr,
			struct switch_val *val)
{
	if (!dev->ops->set_port_link)
		return -EOPNOTSUPP;

	return dev->ops->set_port_link(dev, val->port_vlan, val->value.link);
}