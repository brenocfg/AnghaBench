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
struct super_block {int dummy; } ;
struct ocfs2_extent_list {int /*<<< orphan*/  l_tree_depth; } ;

/* Variables and functions */
 int OCFS2_SUBALLOC_ALLOC ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int ocfs2_extend_meta_needed (struct ocfs2_extent_list*) ; 
 int ocfs2_quota_trans_credits (struct super_block*) ; 

__attribute__((used)) static inline int ocfs2_calc_extend_credits(struct super_block *sb,
					    struct ocfs2_extent_list *root_el)
{
	int bitmap_blocks, sysfile_bitmap_blocks, extent_blocks;

	/* bitmap dinode, group desc. + relinked group. */
	bitmap_blocks = OCFS2_SUBALLOC_ALLOC;

	/* we might need to shift tree depth so lets assume an
	 * absolute worst case of complete fragmentation.  Even with
	 * that, we only need one update for the dinode, and then
	 * however many metadata chunks needed * a remaining suballoc
	 * alloc. */
	sysfile_bitmap_blocks = 1 +
		(OCFS2_SUBALLOC_ALLOC - 1) * ocfs2_extend_meta_needed(root_el);

	/* this does not include *new* metadata blocks, which are
	 * accounted for in sysfile_bitmap_blocks. root_el +
	 * prev. last_eb_blk + blocks along edge of tree.
	 * calc_symlink_credits passes because we just need 1
	 * credit for the dinode there. */
	extent_blocks = 1 + 1 + le16_to_cpu(root_el->l_tree_depth);

	return bitmap_blocks + sysfile_bitmap_blocks + extent_blocks +
	       ocfs2_quota_trans_credits(sb);
}