#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct super_block {struct ocfs2_super* s_fs_info; } ;
struct path {TYPE_1__* dentry; } ;
struct ocfs2_super {int /*<<< orphan*/  s_clustersize; } ;
struct kstat {int blocks; int size; int /*<<< orphan*/  blksize; } ;
struct inode {int dummy; } ;
struct TYPE_5__ {int ip_dyn_features; } ;
struct TYPE_4__ {struct super_block* d_sb; } ;

/* Variables and functions */
 int ENOENT ; 
 TYPE_3__* OCFS2_I (struct inode*) ; 
 int OCFS2_INLINE_DATA_FL ; 
 struct inode* d_inode (TYPE_1__*) ; 
 int /*<<< orphan*/  generic_fillattr (struct inode*,struct kstat*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_inode_revalidate (TYPE_1__*) ; 
 scalar_t__ unlikely (int) ; 

int ocfs2_getattr(const struct path *path, struct kstat *stat,
		  u32 request_mask, unsigned int flags)
{
	struct inode *inode = d_inode(path->dentry);
	struct super_block *sb = path->dentry->d_sb;
	struct ocfs2_super *osb = sb->s_fs_info;
	int err;

	err = ocfs2_inode_revalidate(path->dentry);
	if (err) {
		if (err != -ENOENT)
			mlog_errno(err);
		goto bail;
	}

	generic_fillattr(inode, stat);
	/*
	 * If there is inline data in the inode, the inode will normally not
	 * have data blocks allocated (it may have an external xattr block).
	 * Report at least one sector for such files, so tools like tar, rsync,
	 * others don't incorrectly think the file is completely sparse.
	 */
	if (unlikely(OCFS2_I(inode)->ip_dyn_features & OCFS2_INLINE_DATA_FL))
		stat->blocks += (stat->size + 511)>>9;

	/* We set the blksize from the cluster size for performance */
	stat->blksize = osb->s_clustersize;

bail:
	return err;
}