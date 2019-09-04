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
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct net_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  boot_opts_group ; 
 int /*<<< orphan*/  mesh_ie_group ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void lbs_persist_config_remove(struct net_device *dev)
{
	sysfs_remove_group(&(dev->dev.kobj), &boot_opts_group);
	sysfs_remove_group(&(dev->dev.kobj), &mesh_ie_group);
}