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
struct inode {int dummy; } ;
struct ext4_inode_info {scalar_t__ i_data; } ;
struct ext4_extent_idx {int dummy; } ;
struct ext4_extent_header {scalar_t__ eh_depth; int /*<<< orphan*/  eh_entries; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 struct ext4_inode_info* EXT4_I (struct inode*) ; 
 struct ext4_extent_idx* EXT_FIRST_INDEX (struct ext4_extent_header*) ; 
 int free_ext_idx (int /*<<< orphan*/ *,struct inode*,struct ext4_extent_idx*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int free_ext_block(handle_t *handle, struct inode *inode)
{
	int i, retval = 0;
	struct ext4_inode_info *ei = EXT4_I(inode);
	struct ext4_extent_header *eh = (struct ext4_extent_header *)ei->i_data;
	struct ext4_extent_idx *ix;
	if (eh->eh_depth == 0)
		/*
		 * No extra blocks allocated for extent meta data
		 */
		return 0;
	ix = EXT_FIRST_INDEX(eh);
	for (i = 0; i < le16_to_cpu(eh->eh_entries); i++, ix++) {
		retval = free_ext_idx(handle, inode, ix);
		if (retval)
			return retval;
	}
	return retval;
}