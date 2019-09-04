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
struct timespec64 {int dummy; } ;
struct path {scalar_t__ dentry; int /*<<< orphan*/  mnt; } ;
struct ovl_fs {int /*<<< orphan*/  upper_mnt; } ;
struct inode {int /*<<< orphan*/  i_atime; TYPE_1__* i_sb; } ;
struct TYPE_4__ {int /*<<< orphan*/  i_atime; } ;
struct TYPE_3__ {struct ovl_fs* s_fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  OVL_I (struct inode*) ; 
 int S_ATIME ; 
 TYPE_2__* d_inode (scalar_t__) ; 
 scalar_t__ ovl_upperdentry_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  touch_atime (struct path*) ; 

int ovl_update_time(struct inode *inode, struct timespec64 *ts, int flags)
{
	if (flags & S_ATIME) {
		struct ovl_fs *ofs = inode->i_sb->s_fs_info;
		struct path upperpath = {
			.mnt = ofs->upper_mnt,
			.dentry = ovl_upperdentry_dereference(OVL_I(inode)),
		};

		if (upperpath.dentry) {
			touch_atime(&upperpath);
			inode->i_atime = d_inode(upperpath.dentry)->i_atime;
		}
	}
	return 0;
}