#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct ocfs2_new_group_input {scalar_t__ group; scalar_t__ chain; scalar_t__ clusters; scalar_t__ frees; } ;
struct TYPE_3__ {int /*<<< orphan*/  cl_next_free_rec; int /*<<< orphan*/  cl_cpg; int /*<<< orphan*/  cl_count; } ;
struct TYPE_4__ {TYPE_1__ i_chain; } ;
struct ocfs2_dinode {int /*<<< orphan*/  i_clusters; TYPE_2__ id2; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ML_ERROR ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ ocfs2_blocks_to_clusters (int /*<<< orphan*/ ,scalar_t__) ; 
 int ocfs2_check_new_group (struct inode*,struct ocfs2_dinode*,struct ocfs2_new_group_input*,struct buffer_head*) ; 
 scalar_t__ ocfs2_which_cluster_group (struct inode*,scalar_t__) ; 

__attribute__((used)) static int ocfs2_verify_group_and_input(struct inode *inode,
					struct ocfs2_dinode *di,
					struct ocfs2_new_group_input *input,
					struct buffer_head *group_bh)
{
	u16 cl_count = le16_to_cpu(di->id2.i_chain.cl_count);
	u16 cl_cpg = le16_to_cpu(di->id2.i_chain.cl_cpg);
	u16 next_free = le16_to_cpu(di->id2.i_chain.cl_next_free_rec);
	u32 cluster = ocfs2_blocks_to_clusters(inode->i_sb, input->group);
	u32 total_clusters = le32_to_cpu(di->i_clusters);
	int ret = -EINVAL;

	if (cluster < total_clusters)
		mlog(ML_ERROR, "add a group which is in the current volume.\n");
	else if (input->chain >= cl_count)
		mlog(ML_ERROR, "input chain exceeds the limit.\n");
	else if (next_free != cl_count && next_free != input->chain)
		mlog(ML_ERROR,
		     "the add group should be in chain %u\n", next_free);
	else if (total_clusters + input->clusters < total_clusters)
		mlog(ML_ERROR, "add group's clusters overflow.\n");
	else if (input->clusters > cl_cpg)
		mlog(ML_ERROR, "the cluster exceeds the maximum of a group\n");
	else if (input->frees > input->clusters)
		mlog(ML_ERROR, "the free cluster exceeds the total clusters\n");
	else if (total_clusters % cl_cpg != 0)
		mlog(ML_ERROR,
		     "the last group isn't full. Use group extend first.\n");
	else if (input->group != ocfs2_which_cluster_group(inode, cluster))
		mlog(ML_ERROR, "group blkno is invalid\n");
	else if ((ret = ocfs2_check_new_group(inode, di, input, group_bh)))
		mlog(ML_ERROR, "group descriptor check failed.\n");
	else
		ret = 0;

	return ret;
}