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
 int /*<<< orphan*/  fs_kobj ; 
 int sysfs_create_mount_point (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int smk_init_sysfs(void)
{
	return sysfs_create_mount_point(fs_kobj, "smackfs");
}