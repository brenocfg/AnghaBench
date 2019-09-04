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
struct inode {TYPE_1__* i_sb; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;
typedef  scalar_t__ __le32 ;
struct TYPE_2__ {int s_blocksize; } ;

/* Variables and functions */
 int EXT4_FREE_BLOCKS_FORGET ; 
 int EXT4_FREE_BLOCKS_METADATA ; 
 scalar_t__ IS_ERR (struct buffer_head*) ; 
 int PTR_ERR (struct buffer_head*) ; 
 int /*<<< orphan*/  ext4_free_blocks (int /*<<< orphan*/ *,struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 struct buffer_head* ext4_sb_bread (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extend_credit_for_blkdel (int /*<<< orphan*/ *,struct inode*) ; 
 int /*<<< orphan*/  le32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  put_bh (struct buffer_head*) ; 

__attribute__((used)) static int free_dind_blocks(handle_t *handle,
				struct inode *inode, __le32 i_data)
{
	int i;
	__le32 *tmp_idata;
	struct buffer_head *bh;
	unsigned long max_entries = inode->i_sb->s_blocksize >> 2;

	bh = ext4_sb_bread(inode->i_sb, le32_to_cpu(i_data), 0);
	if (IS_ERR(bh))
		return PTR_ERR(bh);

	tmp_idata = (__le32 *)bh->b_data;
	for (i = 0; i < max_entries; i++) {
		if (tmp_idata[i]) {
			extend_credit_for_blkdel(handle, inode);
			ext4_free_blocks(handle, inode, NULL,
					 le32_to_cpu(tmp_idata[i]), 1,
					 EXT4_FREE_BLOCKS_METADATA |
					 EXT4_FREE_BLOCKS_FORGET);
		}
	}
	put_bh(bh);
	extend_credit_for_blkdel(handle, inode);
	ext4_free_blocks(handle, inode, NULL, le32_to_cpu(i_data), 1,
			 EXT4_FREE_BLOCKS_METADATA |
			 EXT4_FREE_BLOCKS_FORGET);
	return 0;
}