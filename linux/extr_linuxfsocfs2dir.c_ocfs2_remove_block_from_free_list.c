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
struct ocfs2_dx_root_block {int /*<<< orphan*/  dr_free_blk; } ;
struct ocfs2_dir_lookup_result {struct buffer_head* dl_leaf_bh; struct buffer_head* dl_prev_leaf_bh; struct buffer_head* dl_dx_root_bh; } ;
struct ocfs2_dir_block_trailer {int /*<<< orphan*/  db_free_next; int /*<<< orphan*/  db_free_rec_len; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 scalar_t__ ocfs2_free_list_at_root (struct ocfs2_dir_lookup_result*) ; 
 int /*<<< orphan*/  ocfs2_journal_dirty (int /*<<< orphan*/ *,struct buffer_head*) ; 
 struct ocfs2_dir_block_trailer* ocfs2_trailer_from_bh (struct buffer_head*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ocfs2_remove_block_from_free_list(struct inode *dir,
				       handle_t *handle,
				       struct ocfs2_dir_lookup_result *lookup)
{
	struct ocfs2_dir_block_trailer *trailer, *prev;
	struct ocfs2_dx_root_block *dx_root;
	struct buffer_head *bh;

	trailer = ocfs2_trailer_from_bh(lookup->dl_leaf_bh, dir->i_sb);

	if (ocfs2_free_list_at_root(lookup)) {
		bh = lookup->dl_dx_root_bh;
		dx_root = (struct ocfs2_dx_root_block *)bh->b_data;
		dx_root->dr_free_blk = trailer->db_free_next;
	} else {
		bh = lookup->dl_prev_leaf_bh;
		prev = ocfs2_trailer_from_bh(bh, dir->i_sb);
		prev->db_free_next = trailer->db_free_next;
	}

	trailer->db_free_rec_len = cpu_to_le16(0);
	trailer->db_free_next = cpu_to_le64(0);

	ocfs2_journal_dirty(handle, bh);
	ocfs2_journal_dirty(handle, lookup->dl_leaf_bh);
}