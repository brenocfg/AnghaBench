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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct ext4_extent_idx {int dummy; } ;
struct ext4_extent_header {scalar_t__ eh_depth; int /*<<< orphan*/  eh_entries; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;
typedef  int /*<<< orphan*/  ext4_fsblk_t ;

/* Variables and functions */
 int EXT4_FREE_BLOCKS_FORGET ; 
 int EXT4_FREE_BLOCKS_METADATA ; 
 struct ext4_extent_idx* EXT_FIRST_INDEX (struct ext4_extent_header*) ; 
 scalar_t__ IS_ERR (struct buffer_head*) ; 
 int PTR_ERR (struct buffer_head*) ; 
 int /*<<< orphan*/  ext4_free_blocks (int /*<<< orphan*/ *,struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ext4_idx_pblock (struct ext4_extent_idx*) ; 
 struct buffer_head* ext4_sb_bread (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extend_credit_for_blkdel (int /*<<< orphan*/ *,struct inode*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_bh (struct buffer_head*) ; 

__attribute__((used)) static int free_ext_idx(handle_t *handle, struct inode *inode,
					struct ext4_extent_idx *ix)
{
	int i, retval = 0;
	ext4_fsblk_t block;
	struct buffer_head *bh;
	struct ext4_extent_header *eh;

	block = ext4_idx_pblock(ix);
	bh = ext4_sb_bread(inode->i_sb, block, 0);
	if (IS_ERR(bh))
		return PTR_ERR(bh);

	eh = (struct ext4_extent_header *)bh->b_data;
	if (eh->eh_depth != 0) {
		ix = EXT_FIRST_INDEX(eh);
		for (i = 0; i < le16_to_cpu(eh->eh_entries); i++, ix++) {
			retval = free_ext_idx(handle, inode, ix);
			if (retval)
				break;
		}
	}
	put_bh(bh);
	extend_credit_for_blkdel(handle, inode);
	ext4_free_blocks(handle, inode, NULL, block, 1,
			 EXT4_FREE_BLOCKS_METADATA | EXT4_FREE_BLOCKS_FORGET);
	return retval;
}