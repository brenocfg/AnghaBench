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
struct device {int /*<<< orphan*/  kobj; } ;
struct ath5k_hw {struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath5k_attribute_group_ani ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
ath5k_sysfs_unregister(struct ath5k_hw *ah)
{
	struct device *dev = ah->dev;

	sysfs_remove_group(&dev->kobj, &ath5k_attribute_group_ani);
}