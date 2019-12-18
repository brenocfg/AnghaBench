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
typedef  scalar_t__ u64 ;
struct ocfs2_dx_root_block {int /*<<< orphan*/  dr_free_blk; } ;
struct ocfs2_dir_lookup_result {struct buffer_head* dl_prev_leaf_bh; struct buffer_head* dl_leaf_bh; } ;
struct ocfs2_dir_block_trailer {int /*<<< orphan*/  db_free_next; int /*<<< orphan*/  db_free_rec_len; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct buffer_head {scalar_t__ b_data; } ;

/* Variables and functions */
 int ENOSPC ; 
 int OCFS2_DIR_REC_LEN (int) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_read_dir_block_direct (struct inode*,scalar_t__,struct buffer_head**) ; 
 struct ocfs2_dir_block_trailer* ocfs2_trailer_from_bh (struct buffer_head*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_search_dx_free_list(struct inode *dir,
				     struct buffer_head *dx_root_bh,
				     int namelen,
				     struct ocfs2_dir_lookup_result *lookup)
{
	int ret = -ENOSPC;
	struct buffer_head *leaf_bh = NULL, *prev_leaf_bh = NULL;
	struct ocfs2_dir_block_trailer *db;
	u64 next_block;
	int rec_len = OCFS2_DIR_REC_LEN(namelen);
	struct ocfs2_dx_root_block *dx_root;

	dx_root = (struct ocfs2_dx_root_block *)dx_root_bh->b_data;
	next_block = le64_to_cpu(dx_root->dr_free_blk);

	while (next_block) {
		brelse(prev_leaf_bh);
		prev_leaf_bh = leaf_bh;
		leaf_bh = NULL;

		ret = ocfs2_read_dir_block_direct(dir, next_block, &leaf_bh);
		if (ret) {
			mlog_errno(ret);
			goto out;
		}

		db = ocfs2_trailer_from_bh(leaf_bh, dir->i_sb);
		if (rec_len <= le16_to_cpu(db->db_free_rec_len)) {
			lookup->dl_leaf_bh = leaf_bh;
			lookup->dl_prev_leaf_bh = prev_leaf_bh;
			leaf_bh = NULL;
			prev_leaf_bh = NULL;
			break;
		}

		next_block = le64_to_cpu(db->db_free_next);
	}

	if (!next_block)
		ret = -ENOSPC;

out:

	brelse(leaf_bh);
	brelse(prev_leaf_bh);
	return ret;
}