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
struct path {scalar_t__ mnt; int /*<<< orphan*/  dentry; } ;
struct TYPE_2__ {scalar_t__ index; int /*<<< orphan*/  workdir; } ;
struct ovl_fs {int workdir_locked; TYPE_1__ config; int /*<<< orphan*/  workbasedir; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  dget (int /*<<< orphan*/ ) ; 
 scalar_t__ ovl_inuse_trylock (int /*<<< orphan*/ ) ; 
 int ovl_make_workdir (struct ovl_fs*,struct path*) ; 
 int ovl_mount_dir (int /*<<< orphan*/ ,struct path*) ; 
 int /*<<< orphan*/  ovl_workdir_ok (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_put (struct path*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

__attribute__((used)) static int ovl_get_workdir(struct ovl_fs *ofs, struct path *upperpath)
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

	err = -EBUSY;
	if (ovl_inuse_trylock(ofs->workbasedir)) {
		ofs->workdir_locked = true;
	} else if (ofs->config.index) {
		pr_err("overlayfs: workdir is in-use by another mount, mount with '-o index=off' to override exclusive workdir protection.\n");
		goto out;
	} else {
		pr_warn("overlayfs: workdir is in-use by another mount, accessing files from both mounts will result in undefined behavior.\n");
	}

	err = ovl_make_workdir(ofs, &workpath);
	if (err)
		goto out;

	err = 0;
out:
	path_put(&workpath);

	return err;
}