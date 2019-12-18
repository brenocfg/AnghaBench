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
typedef  int /*<<< orphan*/  u32 ;
struct path {int /*<<< orphan*/  dentry; } ;
struct TYPE_3__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct kstat {int attributes; int attributes_mask; int blocks; int size; TYPE_1__ btime; int /*<<< orphan*/  result_mask; } ;
struct inode {int /*<<< orphan*/  i_mode; } ;
struct TYPE_4__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct f2fs_inode_info {unsigned int i_flags; TYPE_2__ i_crtime; int /*<<< orphan*/  i_extra_isize; } ;
struct f2fs_inode {int dummy; } ;

/* Variables and functions */
 unsigned int F2FS_APPEND_FL ; 
 scalar_t__ F2FS_FITS_IN_INODE (struct f2fs_inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct f2fs_inode_info* F2FS_I (struct inode*) ; 
 unsigned int F2FS_IMMUTABLE_FL ; 
 int /*<<< orphan*/  F2FS_I_SB (struct inode*) ; 
 unsigned int F2FS_NODUMP_FL ; 
 scalar_t__ IS_ENCRYPTED (struct inode*) ; 
 int STATX_ATTR_APPEND ; 
 int STATX_ATTR_ENCRYPTED ; 
 int STATX_ATTR_IMMUTABLE ; 
 int STATX_ATTR_NODUMP ; 
 int /*<<< orphan*/  STATX_BTIME ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 struct inode* d_inode (int /*<<< orphan*/ ) ; 
 scalar_t__ f2fs_has_extra_attr (struct inode*) ; 
 scalar_t__ f2fs_has_inline_data (struct inode*) ; 
 scalar_t__ f2fs_has_inline_dentry (struct inode*) ; 
 scalar_t__ f2fs_sb_has_inode_crtime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_fillattr (struct inode*,struct kstat*) ; 
 int /*<<< orphan*/  i_crtime ; 

int f2fs_getattr(const struct path *path, struct kstat *stat,
		 u32 request_mask, unsigned int query_flags)
{
	struct inode *inode = d_inode(path->dentry);
	struct f2fs_inode_info *fi = F2FS_I(inode);
	struct f2fs_inode *ri;
	unsigned int flags;

	if (f2fs_has_extra_attr(inode) &&
			f2fs_sb_has_inode_crtime(F2FS_I_SB(inode)) &&
			F2FS_FITS_IN_INODE(ri, fi->i_extra_isize, i_crtime)) {
		stat->result_mask |= STATX_BTIME;
		stat->btime.tv_sec = fi->i_crtime.tv_sec;
		stat->btime.tv_nsec = fi->i_crtime.tv_nsec;
	}

	flags = fi->i_flags;
	if (flags & F2FS_APPEND_FL)
		stat->attributes |= STATX_ATTR_APPEND;
	if (IS_ENCRYPTED(inode))
		stat->attributes |= STATX_ATTR_ENCRYPTED;
	if (flags & F2FS_IMMUTABLE_FL)
		stat->attributes |= STATX_ATTR_IMMUTABLE;
	if (flags & F2FS_NODUMP_FL)
		stat->attributes |= STATX_ATTR_NODUMP;

	stat->attributes_mask |= (STATX_ATTR_APPEND |
				  STATX_ATTR_ENCRYPTED |
				  STATX_ATTR_IMMUTABLE |
				  STATX_ATTR_NODUMP);

	generic_fillattr(inode, stat);

	/* we need to show initial sectors used for inline_data/dentries */
	if ((S_ISREG(inode->i_mode) && f2fs_has_inline_data(inode)) ||
					f2fs_has_inline_dentry(inode))
		stat->blocks += (stat->size + 511) >> 9;

	return 0;
}