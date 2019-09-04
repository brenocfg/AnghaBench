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
struct vfsmount {int dummy; } ;
struct TYPE_4__ {struct vfsmount* mnt; } ;
struct file {TYPE_2__ f_path; } ;
struct autofs_sb_info {int /*<<< orphan*/  sb; } ;
struct TYPE_3__ {int how; } ;
struct autofs_dev_ioctl {TYPE_1__ expire; } ;

/* Variables and functions */
 int autofs_do_expire_multi (int /*<<< orphan*/ ,struct vfsmount*,struct autofs_sb_info*,int) ; 

__attribute__((used)) static int autofs_dev_ioctl_expire(struct file *fp,
				   struct autofs_sb_info *sbi,
				   struct autofs_dev_ioctl *param)
{
	struct vfsmount *mnt;
	int how;

	how = param->expire.how;
	mnt = fp->f_path.mnt;

	return autofs_do_expire_multi(sbi->sb, mnt, sbi, how);
}