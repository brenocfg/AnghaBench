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
typedef  int /*<<< orphan*/  u32 ;
struct ocfs2_super {scalar_t__ first_cluster_group_blkno; int /*<<< orphan*/  sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  ocfs2_blocks_to_clusters (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline u32 ocfs2_cluster_from_desc(struct ocfs2_super *osb,
					  u64 bg_blkno)
{
	/* This should work for all block group descriptors as only
	 * the 1st group descriptor of the cluster bitmap is
	 * different. */

	if (bg_blkno == osb->first_cluster_group_blkno)
		return 0;

	/* the rest of the block groups are located at the beginning
	 * of their 1st cluster, so a direct translation just
	 * works. */
	return ocfs2_blocks_to_clusters(osb->sb, bg_blkno);
}