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
struct net_device {int /*<<< orphan*/  name; } ;
struct ipw2100_priv {TYPE_1__* ieee; struct net_device* net_dev; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {unsigned long scan_age; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPW_DEBUG_INFO (char*,...) ; 
 struct ipw2100_priv* dev_get_drvdata (struct device*) ; 
 int kstrtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  strnlen (char const*,size_t) ; 

__attribute__((used)) static ssize_t store_scan_age(struct device *d, struct device_attribute *attr,
			      const char *buf, size_t count)
{
	struct ipw2100_priv *priv = dev_get_drvdata(d);
	struct net_device *dev = priv->net_dev;
	unsigned long val;
	int ret;

	(void)dev;		/* kill unused-var warning for debug-only code */

	IPW_DEBUG_INFO("enter\n");

	ret = kstrtoul(buf, 0, &val);
	if (ret) {
		IPW_DEBUG_INFO("%s: user supplied invalid value.\n", dev->name);
	} else {
		priv->ieee->scan_age = val;
		IPW_DEBUG_INFO("set scan_age = %u\n", priv->ieee->scan_age);
	}

	IPW_DEBUG_INFO("exit\n");
	return strnlen(buf, count);
}