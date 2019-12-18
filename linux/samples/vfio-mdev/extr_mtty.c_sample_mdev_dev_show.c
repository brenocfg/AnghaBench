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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 char* dev_name (struct device*) ; 
 scalar_t__ mdev_from_dev (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

__attribute__((used)) static ssize_t
sample_mdev_dev_show(struct device *dev, struct device_attribute *attr,
		     char *buf)
{
	if (mdev_from_dev(dev))
		return sprintf(buf, "This is MDEV %s\n", dev_name(dev));

	return sprintf(buf, "\n");
}