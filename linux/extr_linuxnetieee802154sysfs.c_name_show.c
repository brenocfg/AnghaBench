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
struct wpan_phy {int /*<<< orphan*/  dev; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {struct wpan_phy wpan_phy; } ;

/* Variables and functions */
 char* dev_name (int /*<<< orphan*/ *) ; 
 TYPE_1__* dev_to_rdev (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

__attribute__((used)) static ssize_t name_show(struct device *dev,
			 struct device_attribute *attr,
			 char *buf)
{
	struct wpan_phy *wpan_phy = &dev_to_rdev(dev)->wpan_phy;

	return sprintf(buf, "%s\n", dev_name(&wpan_phy->dev));
}