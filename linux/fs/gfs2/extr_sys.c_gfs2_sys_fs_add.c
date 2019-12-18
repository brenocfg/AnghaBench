#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_9__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct super_block {int /*<<< orphan*/ * s_fs_info; TYPE_2__* s_bdev; } ;
struct TYPE_12__ {int /*<<< orphan*/  kset; } ;
struct TYPE_10__ {scalar_t__ ar_spectator; } ;
struct gfs2_sbd {TYPE_3__ sd_kobj; int /*<<< orphan*/  sd_table_name; TYPE_1__ sd_args; struct super_block* sd_vfs; } ;
struct TYPE_13__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_11__ {int /*<<< orphan*/  bd_disk; } ;

/* Variables and functions */
 int /*<<< orphan*/  KOBJ_ADD ; 
 TYPE_9__* disk_to_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fs_err (struct gfs2_sbd*,char*,int) ; 
 int /*<<< orphan*/  gfs2_kset ; 
 int /*<<< orphan*/  gfs2_ktype ; 
 int kobject_init_and_add (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobject_put (TYPE_3__*) ; 
 int /*<<< orphan*/  kobject_uevent_env (TYPE_3__*,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  lock_module_group ; 
 int sb_rdonly (struct super_block*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int sysfs_create_group (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int sysfs_create_link (TYPE_3__*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sysfs_remove_group (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tune_group ; 

int gfs2_sys_fs_add(struct gfs2_sbd *sdp)
{
	struct super_block *sb = sdp->sd_vfs;
	int error;
	char ro[20];
	char spectator[20];
	char *envp[] = { ro, spectator, NULL };

	sprintf(ro, "RDONLY=%d", sb_rdonly(sb));
	sprintf(spectator, "SPECTATOR=%d", sdp->sd_args.ar_spectator ? 1 : 0);

	sdp->sd_kobj.kset = gfs2_kset;
	error = kobject_init_and_add(&sdp->sd_kobj, &gfs2_ktype, NULL,
				     "%s", sdp->sd_table_name);
	if (error)
		goto fail_reg;

	error = sysfs_create_group(&sdp->sd_kobj, &tune_group);
	if (error)
		goto fail_reg;

	error = sysfs_create_group(&sdp->sd_kobj, &lock_module_group);
	if (error)
		goto fail_tune;

	error = sysfs_create_link(&sdp->sd_kobj,
				  &disk_to_dev(sb->s_bdev->bd_disk)->kobj,
				  "device");
	if (error)
		goto fail_lock_module;

	kobject_uevent_env(&sdp->sd_kobj, KOBJ_ADD, envp);
	return 0;

fail_lock_module:
	sysfs_remove_group(&sdp->sd_kobj, &lock_module_group);
fail_tune:
	sysfs_remove_group(&sdp->sd_kobj, &tune_group);
fail_reg:
	fs_err(sdp, "error %d adding sysfs files\n", error);
	kobject_put(&sdp->sd_kobj);
	sb->s_fs_info = NULL;
	return error;
}