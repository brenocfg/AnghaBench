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
struct eeepc_laptop {int cpufv_disabled; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 struct eeepc_laptop* dev_get_drvdata (struct device*) ; 
 int parse_arg (char const*,int*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

__attribute__((used)) static ssize_t cpufv_disabled_store(struct device *dev,
			   struct device_attribute *attr,
			   const char *buf, size_t count)
{
	struct eeepc_laptop *eeepc = dev_get_drvdata(dev);
	int rv, value;

	rv = parse_arg(buf, &value);
	if (rv < 0)
		return rv;

	switch (value) {
	case 0:
		if (eeepc->cpufv_disabled)
			pr_warn("cpufv enabled (not officially supported on this model)\n");
		eeepc->cpufv_disabled = false;
		return count;
	case 1:
		return -EPERM;
	default:
		return -EINVAL;
	}
}