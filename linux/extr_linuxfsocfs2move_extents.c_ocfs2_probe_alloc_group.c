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
typedef  int u32 ;
struct ocfs2_group_desc {scalar_t__ bg_bitmap; int /*<<< orphan*/  bg_bits; int /*<<< orphan*/  bg_blkno; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct buffer_head {scalar_t__ b_data; } ;

/* Variables and functions */
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int) ; 
 int ocfs2_blocks_to_clusters (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ocfs2_test_bit (int,unsigned long*) ; 

__attribute__((used)) static void ocfs2_probe_alloc_group(struct inode *inode, struct buffer_head *bh,
				    int *goal_bit, u32 move_len, u32 max_hop,
				    u32 *phys_cpos)
{
	int i, used, last_free_bits = 0, base_bit = *goal_bit;
	struct ocfs2_group_desc *gd = (struct ocfs2_group_desc *)bh->b_data;
	u32 base_cpos = ocfs2_blocks_to_clusters(inode->i_sb,
						 le64_to_cpu(gd->bg_blkno));

	for (i = base_bit; i < le16_to_cpu(gd->bg_bits); i++) {

		used = ocfs2_test_bit(i, (unsigned long *)gd->bg_bitmap);
		if (used) {
			/*
			 * we even tried searching the free chunk by jumping
			 * a 'max_hop' distance, but still failed.
			 */
			if ((i - base_bit) > max_hop) {
				*phys_cpos = 0;
				break;
			}

			if (last_free_bits)
				last_free_bits = 0;

			continue;
		} else
			last_free_bits++;

		if (last_free_bits == move_len) {
			*goal_bit = i;
			*phys_cpos = base_cpos + i;
			break;
		}
	}

	mlog(0, "found phys_cpos: %u to fit the wanted moving.\n", *phys_cpos);
}