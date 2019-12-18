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
typedef  unsigned int u64 ;
struct ocfs2_super {unsigned int s_clustersize; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_2__ {scalar_t__ ip_blkno; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 TYPE_1__* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_INODE_UPDATE_CREDITS ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_commit_trans (struct ocfs2_super*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ocfs2_start_trans (struct ocfs2_super*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_update_inode_fsync_trans (int /*<<< orphan*/ *,struct inode*,int) ; 
 int ocfs2_zero_range_for_truncate (struct inode*,int /*<<< orphan*/ *,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  trace_ocfs2_zero_partial_clusters (unsigned long long,unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  trace_ocfs2_zero_partial_clusters_range1 (unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  trace_ocfs2_zero_partial_clusters_range2 (unsigned long long,unsigned long long) ; 

__attribute__((used)) static int ocfs2_zero_partial_clusters(struct inode *inode,
				       u64 start, u64 len)
{
	int ret = 0;
	u64 tmpend = 0;
	u64 end = start + len;
	struct ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	unsigned int csize = osb->s_clustersize;
	handle_t *handle;

	/*
	 * The "start" and "end" values are NOT necessarily part of
	 * the range whose allocation is being deleted. Rather, this
	 * is what the user passed in with the request. We must zero
	 * partial clusters here. There's no need to worry about
	 * physical allocation - the zeroing code knows to skip holes.
	 */
	trace_ocfs2_zero_partial_clusters(
		(unsigned long long)OCFS2_I(inode)->ip_blkno,
		(unsigned long long)start, (unsigned long long)end);

	/*
	 * If both edges are on a cluster boundary then there's no
	 * zeroing required as the region is part of the allocation to
	 * be truncated.
	 */
	if ((start & (csize - 1)) == 0 && (end & (csize - 1)) == 0)
		goto out;

	handle = ocfs2_start_trans(osb, OCFS2_INODE_UPDATE_CREDITS);
	if (IS_ERR(handle)) {
		ret = PTR_ERR(handle);
		mlog_errno(ret);
		goto out;
	}

	/*
	 * If start is on a cluster boundary and end is somewhere in another
	 * cluster, we have not COWed the cluster starting at start, unless
	 * end is also within the same cluster. So, in this case, we skip this
	 * first call to ocfs2_zero_range_for_truncate() truncate and move on
	 * to the next one.
	 */
	if ((start & (csize - 1)) != 0) {
		/*
		 * We want to get the byte offset of the end of the 1st
		 * cluster.
		 */
		tmpend = (u64)osb->s_clustersize +
			(start & ~(osb->s_clustersize - 1));
		if (tmpend > end)
			tmpend = end;

		trace_ocfs2_zero_partial_clusters_range1(
			(unsigned long long)start,
			(unsigned long long)tmpend);

		ret = ocfs2_zero_range_for_truncate(inode, handle, start,
						    tmpend);
		if (ret)
			mlog_errno(ret);
	}

	if (tmpend < end) {
		/*
		 * This may make start and end equal, but the zeroing
		 * code will skip any work in that case so there's no
		 * need to catch it up here.
		 */
		start = end & ~(osb->s_clustersize - 1);

		trace_ocfs2_zero_partial_clusters_range2(
			(unsigned long long)start, (unsigned long long)end);

		ret = ocfs2_zero_range_for_truncate(inode, handle, start, end);
		if (ret)
			mlog_errno(ret);
	}
	ocfs2_update_inode_fsync_trans(handle, inode, 1);

	ocfs2_commit_trans(osb, handle);
out:
	return ret;
}