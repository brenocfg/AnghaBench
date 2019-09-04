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
struct eeepc_laptop {TYPE_2__* platform_device; } ;
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  platform_attribute_group ; 
 int /*<<< orphan*/  platform_device_unregister (TYPE_2__*) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void eeepc_platform_exit(struct eeepc_laptop *eeepc)
{
	sysfs_remove_group(&eeepc->platform_device->dev.kobj,
			   &platform_attribute_group);
	platform_device_unregister(eeepc->platform_device);
}