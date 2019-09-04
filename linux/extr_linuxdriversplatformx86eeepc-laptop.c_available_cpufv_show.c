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
struct eeepc_laptop {int dummy; } ;
struct eeepc_cpufv {int num; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ENODEV ; 
 struct eeepc_laptop* dev_get_drvdata (struct device*) ; 
 scalar_t__ get_cpufv (struct eeepc_laptop*,struct eeepc_cpufv*) ; 
 int sprintf (char*,char*,...) ; 

__attribute__((used)) static ssize_t available_cpufv_show(struct device *dev,
				    struct device_attribute *attr,
				    char *buf)
{
	struct eeepc_laptop *eeepc = dev_get_drvdata(dev);
	struct eeepc_cpufv c;
	int i;
	ssize_t len = 0;

	if (get_cpufv(eeepc, &c))
		return -ENODEV;
	for (i = 0; i < c.num; i++)
		len += sprintf(buf + len, "%d ", i);
	len += sprintf(buf + len, "\n");
	return len;
}