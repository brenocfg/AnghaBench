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
struct device {int dummy; } ;

/* Variables and functions */
 int apb_ctrl_coldboot (struct device*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 

__attribute__((used)) static int apb_cold_boot(struct device *dev, void *data)
{
	int ret;

	ret = apb_ctrl_coldboot(dev);
	if (ret)
		dev_warn(dev, "failed to coldboot\n");

	/*Child nodes are independent, so do not exit coldboot operation */
	return 0;
}