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

/* Variables and functions */
 int /*<<< orphan*/  fuse_kobj ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysfs_remove_mount_point (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void fuse_sysfs_cleanup(void)
{
	sysfs_remove_mount_point(fuse_kobj, "connections");
	kobject_put(fuse_kobj);
}