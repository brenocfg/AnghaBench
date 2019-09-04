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
struct fcoe_fcf_device {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 struct fcoe_fcf_device* dev_to_fcf (struct device*) ; 
 int fcoe_fcf_set_dev_loss_tmo (struct fcoe_fcf_device*,unsigned long) ; 
 int fcoe_str_to_dev_loss (char const*,unsigned long*) ; 

__attribute__((used)) static ssize_t
store_fcoe_fcf_dev_loss_tmo(struct device *dev, struct device_attribute *attr,
			    const char *buf, size_t count)
{
	struct fcoe_fcf_device *fcf = dev_to_fcf(dev);
	unsigned long val;
	int rc;

	rc = fcoe_str_to_dev_loss(buf, &val);
	if (rc)
		return rc;

	rc = fcoe_fcf_set_dev_loss_tmo(fcf, val);
	if (rc)
		return rc;
	return count;
}