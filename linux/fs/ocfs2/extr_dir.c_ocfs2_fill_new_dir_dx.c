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
struct ocfs2_super {int dummy; } ;
struct ocfs2_dx_entry_list {int dummy; } ;
struct ocfs2_dx_root_block {struct ocfs2_dx_entry_list dr_entries; } ;
struct ocfs2_dx_hinfo {int dummy; } ;
struct ocfs2_alloc_context {int dummy; } ;
struct inode {int dummy; } ;
struct buffer_head {int /*<<< orphan*/  b_blocknr; scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_dx_dir_attach_index (struct ocfs2_super*,int /*<<< orphan*/ *,struct inode*,struct buffer_head*,struct buffer_head*,struct ocfs2_alloc_context*,int,int,struct buffer_head**) ; 
 int /*<<< orphan*/  ocfs2_dx_dir_name_hash (struct inode*,char*,int,struct ocfs2_dx_hinfo*) ; 
 int /*<<< orphan*/  ocfs2_dx_entry_list_insert (struct ocfs2_dx_entry_list*,struct ocfs2_dx_hinfo*,int /*<<< orphan*/ ) ; 
 int ocfs2_fill_new_dir_el (struct ocfs2_super*,int /*<<< orphan*/ *,struct inode*,struct inode*,struct buffer_head*,struct ocfs2_alloc_context*,struct buffer_head**) ; 

__attribute__((used)) static int ocfs2_fill_new_dir_dx(struct ocfs2_super *osb,
				 handle_t *handle,
				 struct inode *parent,
				 struct inode *inode,
				 struct buffer_head *di_bh,
				 struct ocfs2_alloc_context *data_ac,
				 struct ocfs2_alloc_context *meta_ac)
{
	int ret;
	struct buffer_head *leaf_bh = NULL;
	struct buffer_head *dx_root_bh = NULL;
	struct ocfs2_dx_hinfo hinfo;
	struct ocfs2_dx_root_block *dx_root;
	struct ocfs2_dx_entry_list *entry_list;

	/*
	 * Our strategy is to create the directory as though it were
	 * unindexed, then add the index block. This works with very
	 * little complication since the state of a new directory is a
	 * very well known quantity.
	 *
	 * Essentially, we have two dirents ("." and ".."), in the 1st
	 * block which need indexing. These are easily inserted into
	 * the index block.
	 */

	ret = ocfs2_fill_new_dir_el(osb, handle, parent, inode, di_bh,
				    data_ac, &leaf_bh);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	ret = ocfs2_dx_dir_attach_index(osb, handle, inode, di_bh, leaf_bh,
					meta_ac, 1, 2, &dx_root_bh);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}
	dx_root = (struct ocfs2_dx_root_block *)dx_root_bh->b_data;
	entry_list = &dx_root->dr_entries;

	/* Buffer has been journaled for us by ocfs2_dx_dir_attach_index */
	ocfs2_dx_dir_name_hash(inode, ".", 1, &hinfo);
	ocfs2_dx_entry_list_insert(entry_list, &hinfo, leaf_bh->b_blocknr);

	ocfs2_dx_dir_name_hash(inode, "..", 2, &hinfo);
	ocfs2_dx_entry_list_insert(entry_list, &hinfo, leaf_bh->b_blocknr);

out:
	brelse(dx_root_bh);
	brelse(leaf_bh);
	return ret;
}