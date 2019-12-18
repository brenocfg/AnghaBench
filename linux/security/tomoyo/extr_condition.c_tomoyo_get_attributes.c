#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_5__ {struct dentry* dentry; } ;
struct TYPE_4__ {struct dentry* dentry; } ;
struct tomoyo_obj_info {int* stat_valid; struct tomoyo_mini_stat* stat; TYPE_2__ path2; TYPE_1__ path1; } ;
struct tomoyo_mini_stat {int /*<<< orphan*/  rdev; int /*<<< orphan*/  dev; int /*<<< orphan*/  mode; int /*<<< orphan*/  ino; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;
struct inode {int /*<<< orphan*/  i_rdev; TYPE_3__* i_sb; int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; } ;
struct dentry {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  s_dev; } ;

/* Variables and functions */
 int TOMOYO_MAX_PATH_STAT ; 
#define  TOMOYO_PATH1 129 
#define  TOMOYO_PATH2 128 
 struct inode* d_backing_inode (struct dentry*) ; 
 struct dentry* dget_parent (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 

void tomoyo_get_attributes(struct tomoyo_obj_info *obj)
{
	u8 i;
	struct dentry *dentry = NULL;

	for (i = 0; i < TOMOYO_MAX_PATH_STAT; i++) {
		struct inode *inode;

		switch (i) {
		case TOMOYO_PATH1:
			dentry = obj->path1.dentry;
			if (!dentry)
				continue;
			break;
		case TOMOYO_PATH2:
			dentry = obj->path2.dentry;
			if (!dentry)
				continue;
			break;
		default:
			if (!dentry)
				continue;
			dentry = dget_parent(dentry);
			break;
		}
		inode = d_backing_inode(dentry);
		if (inode) {
			struct tomoyo_mini_stat *stat = &obj->stat[i];

			stat->uid  = inode->i_uid;
			stat->gid  = inode->i_gid;
			stat->ino  = inode->i_ino;
			stat->mode = inode->i_mode;
			stat->dev  = inode->i_sb->s_dev;
			stat->rdev = inode->i_rdev;
			obj->stat_valid[i] = true;
		}
		if (i & 1) /* TOMOYO_PATH1_PARENT or TOMOYO_PATH2_PARENT */
			dput(dentry);
	}
}