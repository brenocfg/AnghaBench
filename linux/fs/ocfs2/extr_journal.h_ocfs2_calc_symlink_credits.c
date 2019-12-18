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

/* Variables and functions */
 scalar_t__ ocfs2_clusters_to_blocks (struct super_block*,int) ; 
 int ocfs2_mknod_credits (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ocfs2_quota_trans_credits (struct super_block*) ; 

__attribute__((used)) static inline int ocfs2_calc_symlink_credits(struct super_block *sb)
{
	int blocks = ocfs2_mknod_credits(sb, 0, 0);

	/* links can be longer than one block so we may update many
	 * within our single allocated extent. */
	blocks += ocfs2_clusters_to_blocks(sb, 1);

	return blocks + ocfs2_quota_trans_credits(sb);
}