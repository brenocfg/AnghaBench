#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ocfs2_super {int /*<<< orphan*/  dev_str; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_sb; } ;
struct ocfs2_inode_info {int ip_dyn_features; scalar_t__ ip_clusters; scalar_t__ ip_blkno; TYPE_1__ vfs_inode; } ;
struct ocfs2_extent_tree {int /*<<< orphan*/  et_ci; } ;
struct ocfs2_extent_rec {int /*<<< orphan*/  e_cpos; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int OCFS2_INLINE_DATA_FL ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 struct ocfs2_inode_info* cache_info_to_inode (int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_bug_on_msg (int,char*,int /*<<< orphan*/ ,unsigned long long,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ocfs2_sparse_alloc (struct ocfs2_super*) ; 

__attribute__((used)) static int ocfs2_dinode_insert_check(struct ocfs2_extent_tree *et,
				     struct ocfs2_extent_rec *rec)
{
	struct ocfs2_inode_info *oi = cache_info_to_inode(et->et_ci);
	struct ocfs2_super *osb = OCFS2_SB(oi->vfs_inode.i_sb);

	BUG_ON(oi->ip_dyn_features & OCFS2_INLINE_DATA_FL);
	mlog_bug_on_msg(!ocfs2_sparse_alloc(osb) &&
			(oi->ip_clusters != le32_to_cpu(rec->e_cpos)),
			"Device %s, asking for sparse allocation: inode %llu, "
			"cpos %u, clusters %u\n",
			osb->dev_str,
			(unsigned long long)oi->ip_blkno,
			rec->e_cpos, oi->ip_clusters);

	return 0;
}