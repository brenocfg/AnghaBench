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
 scalar_t__ iucv_path_connected ; 
 int /*<<< orphan*/  iucv_path_sever (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ smsg_path ; 

__attribute__((used)) static int smsg_pm_freeze(struct device *dev)
{
#ifdef CONFIG_PM_DEBUG
	printk(KERN_WARNING "smsg_pm_freeze\n");
#endif
	if (smsg_path && iucv_path_connected) {
		iucv_path_sever(smsg_path, NULL);
		iucv_path_connected = 0;
	}
	return 0;
}