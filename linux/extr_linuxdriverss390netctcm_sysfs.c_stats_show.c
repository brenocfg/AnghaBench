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
struct ctcm_priv {int dummy; } ;
struct ccwgroup_device {scalar_t__ state; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 scalar_t__ CCWGROUP_ONLINE ; 
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  ctcm_print_statistics (struct ctcm_priv*) ; 
 struct ctcm_priv* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 
 struct ccwgroup_device* to_ccwgroupdev (struct device*) ; 

__attribute__((used)) static ssize_t stats_show(struct device *dev,
			  struct device_attribute *attr, char *buf)
{
	struct ccwgroup_device *gdev = to_ccwgroupdev(dev);
	struct ctcm_priv *priv = dev_get_drvdata(dev);

	if (!priv || gdev->state != CCWGROUP_ONLINE)
		return -ENODEV;
	ctcm_print_statistics(priv);
	return sprintf(buf, "0\n");
}