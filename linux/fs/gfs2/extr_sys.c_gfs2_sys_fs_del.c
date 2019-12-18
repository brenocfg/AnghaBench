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
struct gfs2_sbd {int /*<<< orphan*/  sd_kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_module_group ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_link (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  tune_group ; 

void gfs2_sys_fs_del(struct gfs2_sbd *sdp)
{
	sysfs_remove_link(&sdp->sd_kobj, "device");
	sysfs_remove_group(&sdp->sd_kobj, &tune_group);
	sysfs_remove_group(&sdp->sd_kobj, &lock_module_group);
	kobject_put(&sdp->sd_kobj);
}