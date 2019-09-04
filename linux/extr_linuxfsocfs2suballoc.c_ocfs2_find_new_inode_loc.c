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
typedef  int /*<<< orphan*/  u64 ;
struct ocfs2_suballoc_result {int /*<<< orphan*/  sr_blkno; } ;
struct ocfs2_alloc_context {scalar_t__ ac_bits_given; int ac_bits_wanted; scalar_t__ ac_which; int ac_find_loc_only; struct ocfs2_suballoc_result* ac_find_loc_priv; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ OCFS2_AC_USE_INODE ; 
 int /*<<< orphan*/  OCFS2_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OCFS2_SUBALLOC_ALLOC ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ocfs2_suballoc_result*) ; 
 struct ocfs2_suballoc_result* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_claim_suballoc_bits (struct ocfs2_alloc_context*,int /*<<< orphan*/ *,int,int,struct ocfs2_suballoc_result*) ; 
 int /*<<< orphan*/  ocfs2_commit_trans (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_init_inode_ac_group (struct inode*,struct buffer_head*,struct ocfs2_alloc_context*) ; 
 int /*<<< orphan*/ * ocfs2_start_trans (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_update_inode_fsync_trans (int /*<<< orphan*/ *,struct inode*,int /*<<< orphan*/ ) ; 

int ocfs2_find_new_inode_loc(struct inode *dir,
			     struct buffer_head *parent_fe_bh,
			     struct ocfs2_alloc_context *ac,
			     u64 *fe_blkno)
{
	int ret;
	handle_t *handle = NULL;
	struct ocfs2_suballoc_result *res;

	BUG_ON(!ac);
	BUG_ON(ac->ac_bits_given != 0);
	BUG_ON(ac->ac_bits_wanted != 1);
	BUG_ON(ac->ac_which != OCFS2_AC_USE_INODE);

	res = kzalloc(sizeof(*res), GFP_NOFS);
	if (res == NULL) {
		ret = -ENOMEM;
		mlog_errno(ret);
		goto out;
	}

	ocfs2_init_inode_ac_group(dir, parent_fe_bh, ac);

	/*
	 * The handle started here is for chain relink. Alternatively,
	 * we could just disable relink for these calls.
	 */
	handle = ocfs2_start_trans(OCFS2_SB(dir->i_sb), OCFS2_SUBALLOC_ALLOC);
	if (IS_ERR(handle)) {
		ret = PTR_ERR(handle);
		handle = NULL;
		mlog_errno(ret);
		goto out;
	}

	/*
	 * This will instruct ocfs2_claim_suballoc_bits and
	 * ocfs2_search_one_group to search but save actual allocation
	 * for later.
	 */
	ac->ac_find_loc_only = 1;

	ret = ocfs2_claim_suballoc_bits(ac, handle, 1, 1, res);
	if (ret < 0) {
		mlog_errno(ret);
		goto out;
	}

	ac->ac_find_loc_priv = res;
	*fe_blkno = res->sr_blkno;
	ocfs2_update_inode_fsync_trans(handle, dir, 0);
out:
	if (handle)
		ocfs2_commit_trans(OCFS2_SB(dir->i_sb), handle);

	if (ret)
		kfree(res);

	return ret;
}