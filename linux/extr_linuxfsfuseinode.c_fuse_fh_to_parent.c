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
typedef  int u64 ;
struct super_block {int dummy; } ;
struct fuse_inode_handle {int nodeid; scalar_t__ generation; } ;
struct fid {scalar_t__* raw; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 struct dentry* fuse_get_dentry (struct super_block*,struct fuse_inode_handle*) ; 

__attribute__((used)) static struct dentry *fuse_fh_to_parent(struct super_block *sb,
		struct fid *fid, int fh_len, int fh_type)
{
	struct fuse_inode_handle parent;

	if (fh_type != 0x82 || fh_len < 6)
		return NULL;

	parent.nodeid = (u64) fid->raw[3] << 32;
	parent.nodeid |= (u64) fid->raw[4];
	parent.generation = fid->raw[5];
	return fuse_get_dentry(sb, &parent);
}