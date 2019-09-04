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
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct ocfs2_suballoc_result {scalar_t__ sr_bit_offset; scalar_t__ sr_bits; } ;
struct ocfs2_group_desc {int /*<<< orphan*/  bg_blkno; int /*<<< orphan*/  bg_bits; scalar_t__ bg_free_bits_count; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct buffer_head {scalar_t__ b_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOSPC ; 
 int /*<<< orphan*/  OCFS2_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int ocfs2_block_group_find_clear_bits (int /*<<< orphan*/ ,struct buffer_head*,int,int /*<<< orphan*/ ,struct ocfs2_suballoc_result*) ; 
 int ocfs2_is_cluster_bitmap (struct inode*) ; 
 int /*<<< orphan*/  trace_ocfs2_block_group_search_max_block (unsigned long long,unsigned long long) ; 

__attribute__((used)) static int ocfs2_block_group_search(struct inode *inode,
				    struct buffer_head *group_bh,
				    u32 bits_wanted, u32 min_bits,
				    u64 max_block,
				    struct ocfs2_suballoc_result *res)
{
	int ret = -ENOSPC;
	u64 blkoff;
	struct ocfs2_group_desc *bg = (struct ocfs2_group_desc *) group_bh->b_data;

	BUG_ON(min_bits != 1);
	BUG_ON(ocfs2_is_cluster_bitmap(inode));

	if (bg->bg_free_bits_count) {
		ret = ocfs2_block_group_find_clear_bits(OCFS2_SB(inode->i_sb),
							group_bh, bits_wanted,
							le16_to_cpu(bg->bg_bits),
							res);
		if (!ret && max_block) {
			blkoff = le64_to_cpu(bg->bg_blkno) +
				res->sr_bit_offset + res->sr_bits;
			trace_ocfs2_block_group_search_max_block(
				(unsigned long long)blkoff,
				(unsigned long long)max_block);
			if (blkoff > max_block)
				ret = -ENOSPC;
		}
	}

	return ret;
}