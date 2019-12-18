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
struct inode {int dummy; } ;
struct ext4_xattr_ibody_header {scalar_t__ h_magic; } ;
struct ext4_inode {int dummy; } ;
struct ext4_iloc {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_2__ {int i_extra_isize; } ;

/* Variables and functions */
 int EXT4_GOOD_OLD_INODE_SIZE ; 
 TYPE_1__* EXT4_I (struct inode*) ; 
 int /*<<< orphan*/  EXT4_STATE_XATTR ; 
 int /*<<< orphan*/  EXT4_XATTR_MAGIC ; 
 struct ext4_xattr_ibody_header* IHDR (struct inode*,struct ext4_inode*) ; 
 scalar_t__ cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int ext4_expand_extra_isize_ea (struct inode*,unsigned int,struct ext4_inode*,int /*<<< orphan*/ *) ; 
 struct ext4_inode* ext4_raw_inode (struct ext4_iloc*) ; 
 int /*<<< orphan*/  ext4_test_inode_state (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int __ext4_expand_extra_isize(struct inode *inode,
				     unsigned int new_extra_isize,
				     struct ext4_iloc *iloc,
				     handle_t *handle, int *no_expand)
{
	struct ext4_inode *raw_inode;
	struct ext4_xattr_ibody_header *header;
	int error;

	raw_inode = ext4_raw_inode(iloc);

	header = IHDR(inode, raw_inode);

	/* No extended attributes present */
	if (!ext4_test_inode_state(inode, EXT4_STATE_XATTR) ||
	    header->h_magic != cpu_to_le32(EXT4_XATTR_MAGIC)) {
		memset((void *)raw_inode + EXT4_GOOD_OLD_INODE_SIZE +
		       EXT4_I(inode)->i_extra_isize, 0,
		       new_extra_isize - EXT4_I(inode)->i_extra_isize);
		EXT4_I(inode)->i_extra_isize = new_extra_isize;
		return 0;
	}

	/* try to expand with EAs present */
	error = ext4_expand_extra_isize_ea(inode, new_extra_isize,
					   raw_inode, handle);
	if (error) {
		/*
		 * Inode size expansion failed; don't try again
		 */
		*no_expand = 1;
	}

	return error;
}