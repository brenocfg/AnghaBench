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
struct kstat {int attributes; int attributes_mask; TYPE_1__ btime; int /*<<< orphan*/  result_mask; } ;
struct inode {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct ext4_inode_info {unsigned int i_flags; TYPE_2__ i_crtime; } ;
struct ext4_inode {int dummy; } ;

/* Variables and functions */
 unsigned int EXT4_APPEND_FL ; 
 unsigned int EXT4_COMPR_FL ; 
 unsigned int EXT4_ENCRYPT_FL ; 
 scalar_t__ EXT4_FITS_IN_INODE (struct ext4_inode*,struct ext4_inode_info*,int /*<<< orphan*/ ) ; 
 unsigned int EXT4_FL_USER_VISIBLE ; 
 struct ext4_inode_info* EXT4_I (struct inode*) ; 
 unsigned int EXT4_IMMUTABLE_FL ; 
 unsigned int EXT4_NODUMP_FL ; 
 int STATX_ATTR_APPEND ; 
 int STATX_ATTR_COMPRESSED ; 
 int STATX_ATTR_ENCRYPTED ; 
 int STATX_ATTR_IMMUTABLE ; 
 int STATX_ATTR_NODUMP ; 
 int /*<<< orphan*/  STATX_BTIME ; 
 struct inode* d_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_fillattr (struct inode*,struct kstat*) ; 
 int /*<<< orphan*/  i_crtime ; 

int ext4_getattr(const struct path *path, struct kstat *stat,
		 u32 request_mask, unsigned int query_flags)
{
	struct inode *inode = d_inode(path->dentry);
	struct ext4_inode *raw_inode;
	struct ext4_inode_info *ei = EXT4_I(inode);
	unsigned int flags;

	if (EXT4_FITS_IN_INODE(raw_inode, ei, i_crtime)) {
		stat->result_mask |= STATX_BTIME;
		stat->btime.tv_sec = ei->i_crtime.tv_sec;
		stat->btime.tv_nsec = ei->i_crtime.tv_nsec;
	}

	flags = ei->i_flags & EXT4_FL_USER_VISIBLE;
	if (flags & EXT4_APPEND_FL)
		stat->attributes |= STATX_ATTR_APPEND;
	if (flags & EXT4_COMPR_FL)
		stat->attributes |= STATX_ATTR_COMPRESSED;
	if (flags & EXT4_ENCRYPT_FL)
		stat->attributes |= STATX_ATTR_ENCRYPTED;
	if (flags & EXT4_IMMUTABLE_FL)
		stat->attributes |= STATX_ATTR_IMMUTABLE;
	if (flags & EXT4_NODUMP_FL)
		stat->attributes |= STATX_ATTR_NODUMP;

	stat->attributes_mask |= (STATX_ATTR_APPEND |
				  STATX_ATTR_COMPRESSED |
				  STATX_ATTR_ENCRYPTED |
				  STATX_ATTR_IMMUTABLE |
				  STATX_ATTR_NODUMP);

	generic_fillattr(inode, stat);
	return 0;
}