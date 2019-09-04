#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct path {TYPE_5__* dentry; TYPE_2__* mnt; } ;
struct file {int dummy; } ;
struct autofs_sb_info {TYPE_3__* sb; } ;
struct TYPE_13__ {unsigned int devid; unsigned int magic; } ;
struct TYPE_8__ {unsigned int type; } ;
struct TYPE_14__ {TYPE_6__ out; TYPE_1__ in; } ;
struct autofs_dev_ioctl {char* path; int ioctlfd; TYPE_7__ ismountpoint; } ;
typedef  unsigned int dev_t ;
struct TYPE_12__ {TYPE_4__* d_sb; } ;
struct TYPE_11__ {unsigned int s_dev; unsigned int s_magic; } ;
struct TYPE_10__ {unsigned int s_dev; } ;
struct TYPE_9__ {TYPE_5__* mnt_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT_FDCWD ; 
 int ENOENT ; 
 int /*<<< orphan*/  LOOKUP_FOLLOW ; 
 scalar_t__ autofs_type_any (unsigned int) ; 
 int find_autofs_mount (char const*,struct path*,int /*<<< orphan*/ ,unsigned int*) ; 
 scalar_t__ follow_down_one (struct path*) ; 
 int kern_path_mountpoint (int /*<<< orphan*/ ,char const*,struct path*,int /*<<< orphan*/ ) ; 
 unsigned int new_encode_dev (unsigned int) ; 
 int path_has_submounts (struct path*) ; 
 int /*<<< orphan*/  path_put (struct path*) ; 
 int /*<<< orphan*/  test_by_dev ; 
 int /*<<< orphan*/  test_by_type ; 

__attribute__((used)) static int autofs_dev_ioctl_ismountpoint(struct file *fp,
					 struct autofs_sb_info *sbi,
					 struct autofs_dev_ioctl *param)
{
	struct path path;
	const char *name;
	unsigned int type;
	unsigned int devid, magic;
	int err = -ENOENT;

	/* param->path has been checked in validate_dev_ioctl() */

	name = param->path;
	type = param->ismountpoint.in.type;

	param->ismountpoint.out.devid = devid = 0;
	param->ismountpoint.out.magic = magic = 0;

	if (!fp || param->ioctlfd == -1) {
		if (autofs_type_any(type))
			err = kern_path_mountpoint(AT_FDCWD,
						   name, &path, LOOKUP_FOLLOW);
		else
			err = find_autofs_mount(name, &path,
						test_by_type, &type);
		if (err)
			goto out;
		devid = new_encode_dev(path.dentry->d_sb->s_dev);
		err = 0;
		if (path.mnt->mnt_root == path.dentry) {
			err = 1;
			magic = path.dentry->d_sb->s_magic;
		}
	} else {
		dev_t dev = sbi->sb->s_dev;

		err = find_autofs_mount(name, &path, test_by_dev, &dev);
		if (err)
			goto out;

		devid = new_encode_dev(dev);

		err = path_has_submounts(&path);

		if (follow_down_one(&path))
			magic = path.dentry->d_sb->s_magic;
	}

	param->ismountpoint.out.devid = devid;
	param->ismountpoint.out.magic = magic;
	path_put(&path);
out:
	return err;
}