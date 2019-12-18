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
typedef  int u16 ;
struct ocfs2_new_group_input {int chain; int clusters; int frees; } ;
struct ocfs2_group_desc {int /*<<< orphan*/  bg_bits; int /*<<< orphan*/  bg_blkno; int /*<<< orphan*/  bg_free_bits_count; int /*<<< orphan*/  bg_chain; } ;
struct TYPE_3__ {int /*<<< orphan*/  cl_bpc; } ;
struct TYPE_4__ {TYPE_1__ i_chain; } ;
struct ocfs2_dinode {TYPE_2__ id2; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct buffer_head {scalar_t__ b_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned long long,int,int) ; 
 int ocfs2_check_group_descriptor (int /*<<< orphan*/ ,struct ocfs2_dinode*,struct buffer_head*) ; 

__attribute__((used)) static int ocfs2_check_new_group(struct inode *inode,
				 struct ocfs2_dinode *di,
				 struct ocfs2_new_group_input *input,
				 struct buffer_head *group_bh)
{
	int ret;
	struct ocfs2_group_desc *gd =
		(struct ocfs2_group_desc *)group_bh->b_data;
	u16 cl_bpc = le16_to_cpu(di->id2.i_chain.cl_bpc);

	ret = ocfs2_check_group_descriptor(inode->i_sb, di, group_bh);
	if (ret)
		goto out;

	ret = -EINVAL;
	if (le16_to_cpu(gd->bg_chain) != input->chain)
		mlog(ML_ERROR, "Group descriptor # %llu has bad chain %u "
		     "while input has %u set.\n",
		     (unsigned long long)le64_to_cpu(gd->bg_blkno),
		     le16_to_cpu(gd->bg_chain), input->chain);
	else if (le16_to_cpu(gd->bg_bits) != input->clusters * cl_bpc)
		mlog(ML_ERROR, "Group descriptor # %llu has bit count %u but "
		     "input has %u clusters set\n",
		     (unsigned long long)le64_to_cpu(gd->bg_blkno),
		     le16_to_cpu(gd->bg_bits), input->clusters);
	else if (le16_to_cpu(gd->bg_free_bits_count) != input->frees * cl_bpc)
		mlog(ML_ERROR, "Group descriptor # %llu has free bit count %u "
		     "but it should have %u set\n",
		     (unsigned long long)le64_to_cpu(gd->bg_blkno),
		     le16_to_cpu(gd->bg_bits),
		     input->frees * cl_bpc);
	else
		ret = 0;

out:
	return ret;
}