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
struct super_block {int dummy; } ;
struct path {scalar_t__ mnt; int /*<<< orphan*/  dentry; } ;
struct TYPE_2__ {int /*<<< orphan*/  workdir; } ;
struct ovl_fs {int workdir_locked; int /*<<< orphan*/  workbasedir_trap; int /*<<< orphan*/  workbasedir; TYPE_1__ config; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dget (int /*<<< orphan*/ ) ; 
 scalar_t__ ovl_inuse_trylock (int /*<<< orphan*/ ) ; 
 int ovl_make_workdir (struct super_block*,struct ovl_fs*,struct path*) ; 
 int ovl_mount_dir (int /*<<< orphan*/ ,struct path*) ; 
 int ovl_report_in_use (struct ovl_fs*,char*) ; 
 int ovl_setup_trap (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ovl_workdir_ok (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_put (struct path*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int ovl_get_workdir(struct super_block *sb, struct ovl_fs *ofs,
			   struct path *upperpath)
{
	int err;
	struct path workpath = { };

	err = ovl_mount_dir(ofs->config.workdir, &workpath);
	if (err)
		goto out;

	err = -EINVAL;
	if (upperpath->mnt != workpath.mnt) {
		pr_err("overlayfs: workdir and upperdir must reside under the same mount\n");
		goto out;
	}
	if (!ovl_workdir_ok(workpath.dentry, upperpath->dentry)) {
		pr_err("overlayfs: workdir and upperdir must be separate subtrees\n");
		goto out;
	}

	ofs->workbasedir = dget(workpath.dentry);

	if (ovl_inuse_trylock(ofs->workbasedir)) {
		ofs->workdir_locked = true;
	} else {
		err = ovl_report_in_use(ofs, "workdir");
		if (err)
			goto out;
	}

	err = ovl_setup_trap(sb, ofs->workbasedir, &ofs->workbasedir_trap,
			     "workdir");
	if (err)
		goto out;

	err = ovl_make_workdir(sb, ofs, &workpath);

out:
	path_put(&workpath);

	return err;
}