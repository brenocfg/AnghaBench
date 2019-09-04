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
struct powercap_zone {TYPE_2__* ops; } ;
struct powercap_control_type {TYPE_1__* ops; } ;
struct device_attribute {int dummy; } ;
struct device {scalar_t__ parent; } ;
typedef  size_t ssize_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* set_enable ) (struct powercap_zone*,int) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  (* set_enable ) (struct powercap_control_type*,int) ;} ;

/* Variables and functions */
 size_t EINVAL ; 
 size_t ENOSYS ; 
 scalar_t__ strtobool (char const*,int*) ; 
 int /*<<< orphan*/  stub1 (struct powercap_zone*,int) ; 
 int /*<<< orphan*/  stub2 (struct powercap_control_type*,int) ; 
 struct powercap_control_type* to_powercap_control_type (struct device*) ; 
 struct powercap_zone* to_powercap_zone (struct device*) ; 

__attribute__((used)) static ssize_t enabled_store(struct device *dev,
				struct device_attribute *attr,
				const char *buf,  size_t len)
{
	bool mode;

	if (strtobool(buf, &mode))
		return -EINVAL;
	if (dev->parent) {
		struct powercap_zone *power_zone = to_powercap_zone(dev);
		if (power_zone->ops->set_enable)
			if (!power_zone->ops->set_enable(power_zone, mode))
				return len;
	} else {
		struct powercap_control_type *control_type =
						to_powercap_control_type(dev);
		if (control_type->ops && control_type->ops->set_enable)
			if (!control_type->ops->set_enable(control_type, mode))
				return len;
	}

	return -ENOSYS;
}