#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ocfs2_super {int s_clustersize_bits; int s_clustersize; } ;
struct ocfs2_move_extents {scalar_t__ me_goal; int me_len; } ;
struct ocfs2_group_desc {int /*<<< orphan*/  bg_bits; int /*<<< orphan*/  bg_blkno; } ;
struct inode {TYPE_1__* i_sb; } ;
struct buffer_head {scalar_t__ b_data; } ;
struct TYPE_3__ {int s_blocksize_bits; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GLOBAL_BITMAP_SYSTEM_INODE ; 
 int /*<<< orphan*/  OCFS2_INVALID_SLOT ; 
 struct ocfs2_super* OCFS2_SB (TYPE_1__*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ ocfs2_block_to_cluster_start (TYPE_1__*,scalar_t__) ; 
 int ocfs2_find_victim_alloc_group (struct inode*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,struct buffer_head**) ; 

__attribute__((used)) static int ocfs2_validate_and_adjust_move_goal(struct inode *inode,
					       struct ocfs2_move_extents *range)
{
	int ret, goal_bit = 0;

	struct buffer_head *gd_bh = NULL;
	struct ocfs2_group_desc *bg;
	struct ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	int c_to_b = 1 << (osb->s_clustersize_bits -
					inode->i_sb->s_blocksize_bits);

	/*
	 * make goal become cluster aligned.
	 */
	range->me_goal = ocfs2_block_to_cluster_start(inode->i_sb,
						      range->me_goal);
	/*
	 * validate goal sits within global_bitmap, and return the victim
	 * group desc
	 */
	ret = ocfs2_find_victim_alloc_group(inode, range->me_goal,
					    GLOBAL_BITMAP_SYSTEM_INODE,
					    OCFS2_INVALID_SLOT,
					    &goal_bit, &gd_bh);
	if (ret)
		goto out;

	bg = (struct ocfs2_group_desc *)gd_bh->b_data;

	/*
	 * moving goal is not allowd to start with a group desc blok(#0 blk)
	 * let's compromise to the latter cluster.
	 */
	if (range->me_goal == le64_to_cpu(bg->bg_blkno))
		range->me_goal += c_to_b;

	/*
	 * movement is not gonna cross two groups.
	 */
	if ((le16_to_cpu(bg->bg_bits) - goal_bit) * osb->s_clustersize <
								range->me_len) {
		ret = -EINVAL;
		goto out;
	}
	/*
	 * more exact validations/adjustments will be performed later during
	 * moving operation for each extent range.
	 */
	mlog(0, "extents get ready to be moved to #%llu block\n",
	     range->me_goal);

out:
	brelse(gd_bh);

	return ret;
}