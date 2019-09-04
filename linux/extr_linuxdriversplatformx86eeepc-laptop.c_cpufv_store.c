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
struct eeepc_laptop {scalar_t__ cpufv_disabled; } ;
struct eeepc_cpufv {int num; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  CM_ASL_CPUFV ; 
 int EINVAL ; 
 int ENODEV ; 
 int EPERM ; 
 struct eeepc_laptop* dev_get_drvdata (struct device*) ; 
 scalar_t__ get_cpufv (struct eeepc_laptop*,struct eeepc_cpufv*) ; 
 int parse_arg (char const*,int*) ; 
 int set_acpi (struct eeepc_laptop*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ssize_t cpufv_store(struct device *dev,
			   struct device_attribute *attr,
			   const char *buf, size_t count)
{
	struct eeepc_laptop *eeepc = dev_get_drvdata(dev);
	struct eeepc_cpufv c;
	int rv, value;

	if (eeepc->cpufv_disabled)
		return -EPERM;
	if (get_cpufv(eeepc, &c))
		return -ENODEV;
	rv = parse_arg(buf, &value);
	if (rv < 0)
		return rv;
	if (value < 0 || value >= c.num)
		return -EINVAL;
	rv = set_acpi(eeepc, CM_ASL_CPUFV, value);
	if (rv)
		return rv;
	return count;
}