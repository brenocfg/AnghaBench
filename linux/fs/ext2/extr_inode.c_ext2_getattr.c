#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct path {int /*<<< orphan*/  dentry; } ;
struct kstat {int attributes; int attributes_mask; } ;
struct inode {int dummy; } ;
struct ext2_inode_info {unsigned int i_flags; } ;

/* Variables and functions */
 unsigned int EXT2_APPEND_FL ; 
 unsigned int EXT2_COMPR_FL ; 
 unsigned int EXT2_FL_USER_VISIBLE ; 
 struct ext2_inode_info* EXT2_I (struct inode*) ; 
 unsigned int EXT2_IMMUTABLE_FL ; 
 unsigned int EXT2_NODUMP_FL ; 
 int STATX_ATTR_APPEND ; 
 int STATX_ATTR_COMPRESSED ; 
 int STATX_ATTR_ENCRYPTED ; 
 int STATX_ATTR_IMMUTABLE ; 
 int STATX_ATTR_NODUMP ; 
 struct inode* d_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_fillattr (struct inode*,struct kstat*) ; 

int ext2_getattr(const struct path *path, struct kstat *stat,
		u32 request_mask, unsigned int query_flags)
{
	struct inode *inode = d_inode(path->dentry);
	struct ext2_inode_info *ei = EXT2_I(inode);
	unsigned int flags;

	flags = ei->i_flags & EXT2_FL_USER_VISIBLE;
	if (flags & EXT2_APPEND_FL)
		stat->attributes |= STATX_ATTR_APPEND;
	if (flags & EXT2_COMPR_FL)
		stat->attributes |= STATX_ATTR_COMPRESSED;
	if (flags & EXT2_IMMUTABLE_FL)
		stat->attributes |= STATX_ATTR_IMMUTABLE;
	if (flags & EXT2_NODUMP_FL)
		stat->attributes |= STATX_ATTR_NODUMP;
	stat->attributes_mask |= (STATX_ATTR_APPEND |
			STATX_ATTR_COMPRESSED |
			STATX_ATTR_ENCRYPTED |
			STATX_ATTR_IMMUTABLE |
			STATX_ATTR_NODUMP);

	generic_fillattr(inode, stat);
	return 0;
}