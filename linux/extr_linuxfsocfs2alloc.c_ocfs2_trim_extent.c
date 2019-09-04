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
struct super_block {int dummy; } ;
struct ocfs2_super {scalar_t__ first_cluster_group_blkno; } ;
struct ocfs2_group_desc {int /*<<< orphan*/  bg_blkno; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 struct ocfs2_super* OCFS2_SB (struct super_block*) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ ocfs2_clusters_to_blocks (struct super_block*,int /*<<< orphan*/ ) ; 
 int sb_issue_discard (struct super_block*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_ocfs2_trim_extent (struct super_block*,unsigned long long,scalar_t__) ; 

__attribute__((used)) static int ocfs2_trim_extent(struct super_block *sb,
			     struct ocfs2_group_desc *gd,
			     u64 group, u32 start, u32 count)
{
	u64 discard, bcount;
	struct ocfs2_super *osb = OCFS2_SB(sb);

	bcount = ocfs2_clusters_to_blocks(sb, count);
	discard = ocfs2_clusters_to_blocks(sb, start);

	/*
	 * For the first cluster group, the gd->bg_blkno is not at the start
	 * of the group, but at an offset from the start. If we add it while
	 * calculating discard for first group, we will wrongly start fstrim a
	 * few blocks after the desried start block and the range can cross
	 * over into the next cluster group. So, add it only if this is not
	 * the first cluster group.
	 */
	if (group != osb->first_cluster_group_blkno)
		discard += le64_to_cpu(gd->bg_blkno);

	trace_ocfs2_trim_extent(sb, (unsigned long long)discard, bcount);

	return sb_issue_discard(sb, discard, bcount, GFP_NOFS, 0);
}