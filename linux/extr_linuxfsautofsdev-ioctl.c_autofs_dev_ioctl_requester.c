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
struct path {int /*<<< orphan*/  dentry; } ;
struct file {int dummy; } ;
struct autofs_sb_info {int /*<<< orphan*/  fs_lock; TYPE_1__* sb; } ;
struct autofs_info {int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;
struct TYPE_4__ {int uid; int gid; } ;
struct autofs_dev_ioctl {TYPE_2__ requester; int /*<<< orphan*/  path; } ;
typedef  int /*<<< orphan*/  dev_t ;
struct TYPE_3__ {int /*<<< orphan*/  s_dev; } ;

/* Variables and functions */
 int ENOENT ; 
 struct autofs_info* autofs_dentry_ino (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  autofs_expire_wait (struct path*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_user_ns () ; 
 int find_autofs_mount (int /*<<< orphan*/ ,struct path*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int from_kgid_munged (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int from_kuid_munged (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_put (struct path*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_by_dev ; 

__attribute__((used)) static int autofs_dev_ioctl_requester(struct file *fp,
				      struct autofs_sb_info *sbi,
				      struct autofs_dev_ioctl *param)
{
	struct autofs_info *ino;
	struct path path;
	dev_t devid;
	int err = -ENOENT;

	/* param->path has been checked in validate_dev_ioctl() */

	devid = sbi->sb->s_dev;

	param->requester.uid = param->requester.gid = -1;

	err = find_autofs_mount(param->path, &path, test_by_dev, &devid);
	if (err)
		goto out;

	ino = autofs_dentry_ino(path.dentry);
	if (ino) {
		err = 0;
		autofs_expire_wait(&path, 0);
		spin_lock(&sbi->fs_lock);
		param->requester.uid =
			from_kuid_munged(current_user_ns(), ino->uid);
		param->requester.gid =
			from_kgid_munged(current_user_ns(), ino->gid);
		spin_unlock(&sbi->fs_lock);
	}
	path_put(&path);
out:
	return err;
}