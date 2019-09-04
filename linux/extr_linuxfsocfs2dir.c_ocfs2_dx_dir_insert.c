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
struct ocfs2_dx_root_block {int /*<<< orphan*/  dr_num_entries; } ;
struct ocfs2_dir_lookup_result {int /*<<< orphan*/  dl_dx_leaf_bh; TYPE_1__* dl_leaf_bh; int /*<<< orphan*/  dl_hinfo; struct buffer_head* dl_dx_root_bh; } ;
struct inode {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_2__ {int /*<<< orphan*/  b_blocknr; } ;

/* Variables and functions */
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_WRITE ; 
 int __ocfs2_dx_dir_leaf_insert (struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_add_cpu (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_dx_inline_root_insert (struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ocfs2_dx_root_block*) ; 
 scalar_t__ ocfs2_dx_root_inline (struct ocfs2_dx_root_block*) ; 
 int ocfs2_journal_access_dr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_journal_dirty (int /*<<< orphan*/ *,struct buffer_head*) ; 

__attribute__((used)) static int ocfs2_dx_dir_insert(struct inode *dir, handle_t *handle,
			       struct ocfs2_dir_lookup_result *lookup)
{
	int ret = 0;
	struct ocfs2_dx_root_block *dx_root;
	struct buffer_head *dx_root_bh = lookup->dl_dx_root_bh;

	ret = ocfs2_journal_access_dr(handle, INODE_CACHE(dir), dx_root_bh,
				      OCFS2_JOURNAL_ACCESS_WRITE);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	dx_root = (struct ocfs2_dx_root_block *)lookup->dl_dx_root_bh->b_data;
	if (ocfs2_dx_root_inline(dx_root)) {
		ocfs2_dx_inline_root_insert(dir, handle,
					    &lookup->dl_hinfo,
					    lookup->dl_leaf_bh->b_blocknr,
					    dx_root);
	} else {
		ret = __ocfs2_dx_dir_leaf_insert(dir, handle, &lookup->dl_hinfo,
						 lookup->dl_leaf_bh->b_blocknr,
						 lookup->dl_dx_leaf_bh);
		if (ret)
			goto out;
	}

	le32_add_cpu(&dx_root->dr_num_entries, 1);
	ocfs2_journal_dirty(handle, dx_root_bh);

out:
	return ret;
}