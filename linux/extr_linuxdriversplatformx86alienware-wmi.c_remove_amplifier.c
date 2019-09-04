#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;
struct platform_device {TYPE_1__ dev; } ;
struct TYPE_4__ {scalar_t__ amplifier; } ;

/* Variables and functions */
 int /*<<< orphan*/  amplifier_attribute_group ; 
 TYPE_2__* quirks ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void remove_amplifier(struct platform_device *dev)
{
	if (quirks->amplifier > 0)
		sysfs_remove_group(&dev->dev.kobj, &amplifier_attribute_group);
}