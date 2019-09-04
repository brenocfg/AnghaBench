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
struct ocfs2_extent_list {struct ocfs2_extent_rec* l_recs; int /*<<< orphan*/  l_next_free_rec; } ;
struct ocfs2_group_desc {struct ocfs2_extent_list bg_list; } ;
struct ocfs2_extent_rec {int /*<<< orphan*/  e_leaf_clusters; int /*<<< orphan*/  e_blkno; } ;
struct ocfs2_alloc_context {int /*<<< orphan*/  ac_bh; int /*<<< orphan*/  ac_inode; } ;
struct inode {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_free_clusters (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ocfs2_remove_from_cache (int /*<<< orphan*/ ,struct buffer_head*) ; 

__attribute__((used)) static void ocfs2_bg_alloc_cleanup(handle_t *handle,
				   struct ocfs2_alloc_context *cluster_ac,
				   struct inode *alloc_inode,
				   struct buffer_head *bg_bh)
{
	int i, ret;
	struct ocfs2_group_desc *bg;
	struct ocfs2_extent_list *el;
	struct ocfs2_extent_rec *rec;

	if (!bg_bh)
		return;

	bg = (struct ocfs2_group_desc *)bg_bh->b_data;
	el = &bg->bg_list;
	for (i = 0; i < le16_to_cpu(el->l_next_free_rec); i++) {
		rec = &el->l_recs[i];
		ret = ocfs2_free_clusters(handle, cluster_ac->ac_inode,
					  cluster_ac->ac_bh,
					  le64_to_cpu(rec->e_blkno),
					  le16_to_cpu(rec->e_leaf_clusters));
		if (ret)
			mlog_errno(ret);
		/* Try all the clusters to free */
	}

	ocfs2_remove_from_cache(INODE_CACHE(alloc_inode), bg_bh);
	brelse(bg_bh);
}