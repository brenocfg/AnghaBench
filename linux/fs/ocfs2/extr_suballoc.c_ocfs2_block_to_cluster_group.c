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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct ocfs2_super {scalar_t__ first_cluster_group_blkno; int /*<<< orphan*/  sb; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 scalar_t__ ocfs2_blocks_to_clusters (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ocfs2_is_cluster_bitmap (struct inode*) ; 
 scalar_t__ ocfs2_which_cluster_group (struct inode*,scalar_t__) ; 

__attribute__((used)) static inline void ocfs2_block_to_cluster_group(struct inode *inode,
						u64 data_blkno,
						u64 *bg_blkno,
						u16 *bg_bit_off)
{
	struct ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	u32 data_cluster = ocfs2_blocks_to_clusters(osb->sb, data_blkno);

	BUG_ON(!ocfs2_is_cluster_bitmap(inode));

	*bg_blkno = ocfs2_which_cluster_group(inode,
					      data_cluster);

	if (*bg_blkno == osb->first_cluster_group_blkno)
		*bg_bit_off = (u16) data_cluster;
	else
		*bg_bit_off = (u16) ocfs2_blocks_to_clusters(osb->sb,
							     data_blkno - *bg_blkno);
}