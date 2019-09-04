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
struct ocfs2_extent_list {int /*<<< orphan*/ * l_recs; int /*<<< orphan*/  l_next_free_rec; scalar_t__ l_tree_depth; } ;
struct ocfs2_extent_block {struct ocfs2_extent_list h_list; } ;
struct ocfs2_dinode {int /*<<< orphan*/  i_last_eb_blk; } ;
struct inode {int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_sb; } ;
struct buffer_head {scalar_t__ b_blocknr; scalar_t__ b_data; } ;

/* Variables and functions */
 int EROFS ; 
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_error (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned long long) ; 
 scalar_t__ ocfs2_is_empty_extent (int /*<<< orphan*/ *) ; 
 int ocfs2_read_extent_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct buffer_head**) ; 

__attribute__((used)) static int ocfs2_last_eb_is_empty(struct inode *inode,
				  struct ocfs2_dinode *di)
{
	int ret, next_free;
	u64 last_eb_blk = le64_to_cpu(di->i_last_eb_blk);
	struct buffer_head *eb_bh = NULL;
	struct ocfs2_extent_block *eb;
	struct ocfs2_extent_list *el;

	ret = ocfs2_read_extent_block(INODE_CACHE(inode), last_eb_blk, &eb_bh);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	eb = (struct ocfs2_extent_block *) eb_bh->b_data;
	el = &eb->h_list;

	if (el->l_tree_depth) {
		ocfs2_error(inode->i_sb,
			    "Inode %lu has non zero tree depth in leaf block %llu\n",
			    inode->i_ino,
			    (unsigned long long)eb_bh->b_blocknr);
		ret = -EROFS;
		goto out;
	}

	next_free = le16_to_cpu(el->l_next_free_rec);

	if (next_free == 0 ||
	    (next_free == 1 && ocfs2_is_empty_extent(&el->l_recs[0])))
		ret = 1;

out:
	brelse(eb_bh);
	return ret;
}