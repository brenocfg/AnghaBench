#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_sb; } ;
struct ext4_xattr_ibody_header {int dummy; } ;
struct ext4_inode {int dummy; } ;
struct ext4_iloc {int /*<<< orphan*/  bh; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {int s_inode_size; } ;

/* Variables and functions */
 TYPE_1__* EXT4_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXT4_STATE_XATTR ; 
 int /*<<< orphan*/  IFIRST (struct ext4_xattr_ibody_header*) ; 
 struct ext4_xattr_ibody_header* IHDR (struct inode*,struct ext4_inode*) ; 
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ ) ; 
 struct inode* d_inode (struct dentry*) ; 
 int ext4_get_inode_loc (struct inode*,struct ext4_iloc*) ; 
 struct ext4_inode* ext4_raw_inode (struct ext4_iloc*) ; 
 int /*<<< orphan*/  ext4_test_inode_state (struct inode*,int /*<<< orphan*/ ) ; 
 int ext4_xattr_list_entries (struct dentry*,int /*<<< orphan*/ ,char*,size_t) ; 
 int xattr_check_inode (struct inode*,struct ext4_xattr_ibody_header*,void*) ; 

__attribute__((used)) static int
ext4_xattr_ibody_list(struct dentry *dentry, char *buffer, size_t buffer_size)
{
	struct inode *inode = d_inode(dentry);
	struct ext4_xattr_ibody_header *header;
	struct ext4_inode *raw_inode;
	struct ext4_iloc iloc;
	void *end;
	int error;

	if (!ext4_test_inode_state(inode, EXT4_STATE_XATTR))
		return 0;
	error = ext4_get_inode_loc(inode, &iloc);
	if (error)
		return error;
	raw_inode = ext4_raw_inode(&iloc);
	header = IHDR(inode, raw_inode);
	end = (void *)raw_inode + EXT4_SB(inode->i_sb)->s_inode_size;
	error = xattr_check_inode(inode, header, end);
	if (error)
		goto cleanup;
	error = ext4_xattr_list_entries(dentry, IFIRST(header),
					buffer, buffer_size);

cleanup:
	brelse(iloc.bh);
	return error;
}