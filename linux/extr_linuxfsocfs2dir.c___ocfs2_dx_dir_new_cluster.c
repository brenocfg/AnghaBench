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
struct ocfs2_super {int /*<<< orphan*/  sb; } ;
struct ocfs2_alloc_context {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int __ocfs2_claim_clusters (int /*<<< orphan*/ *,struct ocfs2_alloc_context*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_clusters_to_blocks (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ocfs2_dx_dir_format_cluster (struct ocfs2_super*,int /*<<< orphan*/ *,struct inode*,struct buffer_head**,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __ocfs2_dx_dir_new_cluster(struct inode *dir,
				      u32 cpos, handle_t *handle,
				      struct ocfs2_alloc_context *data_ac,
				      struct buffer_head **dx_leaves,
				      int num_dx_leaves, u64 *ret_phys_blkno)
{
	int ret;
	u32 phys, num;
	u64 phys_blkno;
	struct ocfs2_super *osb = OCFS2_SB(dir->i_sb);

	/*
	 * XXX: For create, this should claim cluster for the index
	 * *before* the unindexed insert so that we have a better
	 * chance of contiguousness as the directory grows in number
	 * of entries.
	 */
	ret = __ocfs2_claim_clusters(handle, data_ac, 1, 1, &phys, &num);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	/*
	 * Format the new cluster first. That way, we're inserting
	 * valid data.
	 */
	phys_blkno = ocfs2_clusters_to_blocks(osb->sb, phys);
	ret = ocfs2_dx_dir_format_cluster(osb, handle, dir, dx_leaves,
					  num_dx_leaves, phys_blkno);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	*ret_phys_blkno = phys_blkno;
out:
	return ret;
}