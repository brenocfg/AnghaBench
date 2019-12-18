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
struct super_block {int dummy; } ;
struct ocfs2_extent_rec {int /*<<< orphan*/  e_leaf_clusters; int /*<<< orphan*/  e_blkno; int /*<<< orphan*/  e_cpos; } ;
typedef  enum ocfs2_split_type { ____Placeholder_ocfs2_split_type } ocfs2_split_type ;

/* Variables and functions */
 int SPLIT_LEFT ; 
 int /*<<< orphan*/  le16_add_cpu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_add_cpu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_add_cpu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_clusters_to_blocks (struct super_block*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ocfs2_subtract_from_rec(struct super_block *sb,
				    enum ocfs2_split_type split,
				    struct ocfs2_extent_rec *rec,
				    struct ocfs2_extent_rec *split_rec)
{
	u64 len_blocks;

	len_blocks = ocfs2_clusters_to_blocks(sb,
				le16_to_cpu(split_rec->e_leaf_clusters));

	if (split == SPLIT_LEFT) {
		/*
		 * Region is on the left edge of the existing
		 * record.
		 */
		le32_add_cpu(&rec->e_cpos,
			     le16_to_cpu(split_rec->e_leaf_clusters));
		le64_add_cpu(&rec->e_blkno, len_blocks);
		le16_add_cpu(&rec->e_leaf_clusters,
			     -le16_to_cpu(split_rec->e_leaf_clusters));
	} else {
		/*
		 * Region is on the right edge of the existing
		 * record.
		 */
		le16_add_cpu(&rec->e_leaf_clusters,
			     -le16_to_cpu(split_rec->e_leaf_clusters));
	}
}