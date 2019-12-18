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
typedef  int /*<<< orphan*/  u32 ;
struct ocfs2_extent_rec {int /*<<< orphan*/  e_leaf_clusters; int /*<<< orphan*/  e_cpos; int /*<<< orphan*/  e_blkno; } ;
struct ocfs2_extent_list {struct ocfs2_extent_rec* l_recs; int /*<<< orphan*/  l_next_free_rec; scalar_t__ l_tree_depth; } ;
struct ocfs2_extent_block {struct ocfs2_extent_list h_list; } ;
struct inode {int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_sb; } ;
struct buffer_head {scalar_t__ b_blocknr; scalar_t__ b_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_error (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned long long,...) ; 
 int ocfs2_find_leaf (int /*<<< orphan*/ ,struct ocfs2_extent_list*,int /*<<< orphan*/ ,struct buffer_head**) ; 
 int /*<<< orphan*/  ocfs2_rec_clusters (struct ocfs2_extent_list*,struct ocfs2_extent_rec*) ; 

__attribute__((used)) static int ocfs2_dx_dir_lookup_rec(struct inode *inode,
				   struct ocfs2_extent_list *el,
				   u32 major_hash,
				   u32 *ret_cpos,
				   u64 *ret_phys_blkno,
				   unsigned int *ret_clen)
{
	int ret = 0, i, found;
	struct buffer_head *eb_bh = NULL;
	struct ocfs2_extent_block *eb;
	struct ocfs2_extent_rec *rec = NULL;

	if (el->l_tree_depth) {
		ret = ocfs2_find_leaf(INODE_CACHE(inode), el, major_hash,
				      &eb_bh);
		if (ret) {
			mlog_errno(ret);
			goto out;
		}

		eb = (struct ocfs2_extent_block *) eb_bh->b_data;
		el = &eb->h_list;

		if (el->l_tree_depth) {
			ret = ocfs2_error(inode->i_sb,
					  "Inode %lu has non zero tree depth in btree tree block %llu\n",
					  inode->i_ino,
					  (unsigned long long)eb_bh->b_blocknr);
			goto out;
		}
	}

	found = 0;
	for (i = le16_to_cpu(el->l_next_free_rec) - 1; i >= 0; i--) {
		rec = &el->l_recs[i];

		if (le32_to_cpu(rec->e_cpos) <= major_hash) {
			found = 1;
			break;
		}
	}

	if (!found) {
		ret = ocfs2_error(inode->i_sb,
				  "Inode %lu has bad extent record (%u, %u, 0) in btree\n",
				  inode->i_ino,
				  le32_to_cpu(rec->e_cpos),
				  ocfs2_rec_clusters(el, rec));
		goto out;
	}

	if (ret_phys_blkno)
		*ret_phys_blkno = le64_to_cpu(rec->e_blkno);
	if (ret_cpos)
		*ret_cpos = le32_to_cpu(rec->e_cpos);
	if (ret_clen)
		*ret_clen = le16_to_cpu(rec->e_leaf_clusters);

out:
	brelse(eb_bh);
	return ret;
}