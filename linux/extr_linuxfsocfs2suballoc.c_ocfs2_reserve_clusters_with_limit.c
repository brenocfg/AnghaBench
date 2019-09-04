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
struct ocfs2_super {int dummy; } ;
struct ocfs2_alloc_context {int /*<<< orphan*/ * ac_inode; int /*<<< orphan*/  ac_max_block; int /*<<< orphan*/  ac_bits_wanted; } ;

/* Variables and functions */
 int ALLOC_GROUPS_FROM_GLOBAL ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  inode_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inode_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iput (int /*<<< orphan*/ *) ; 
 struct ocfs2_alloc_context* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 scalar_t__ ocfs2_alloc_should_use_local (struct ocfs2_super*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_free_alloc_context (struct ocfs2_alloc_context*) ; 
 int ocfs2_inode_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ocfs2_inode_unlock (int /*<<< orphan*/ *,int) ; 
 int ocfs2_reserve_cluster_bitmap_bits (struct ocfs2_super*,struct ocfs2_alloc_context*) ; 
 int ocfs2_reserve_local_alloc_bits (struct ocfs2_super*,int /*<<< orphan*/ ,struct ocfs2_alloc_context*) ; 
 int ocfs2_try_to_free_truncate_log (struct ocfs2_super*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_reserve_clusters_with_limit(struct ocfs2_super *osb,
					     u32 bits_wanted, u64 max_block,
					     int flags,
					     struct ocfs2_alloc_context **ac)
{
	int status, ret = 0;
	int retried = 0;

	*ac = kzalloc(sizeof(struct ocfs2_alloc_context), GFP_KERNEL);
	if (!(*ac)) {
		status = -ENOMEM;
		mlog_errno(status);
		goto bail;
	}

	(*ac)->ac_bits_wanted = bits_wanted;
	(*ac)->ac_max_block = max_block;

	status = -ENOSPC;
	if (!(flags & ALLOC_GROUPS_FROM_GLOBAL) &&
	    ocfs2_alloc_should_use_local(osb, bits_wanted)) {
		status = ocfs2_reserve_local_alloc_bits(osb,
							bits_wanted,
							*ac);
		if ((status < 0) && (status != -ENOSPC)) {
			mlog_errno(status);
			goto bail;
		}
	}

	if (status == -ENOSPC) {
retry:
		status = ocfs2_reserve_cluster_bitmap_bits(osb, *ac);
		/* Retry if there is sufficient space cached in truncate log */
		if (status == -ENOSPC && !retried) {
			retried = 1;
			ocfs2_inode_unlock((*ac)->ac_inode, 1);
			inode_unlock((*ac)->ac_inode);

			ret = ocfs2_try_to_free_truncate_log(osb, bits_wanted);
			if (ret == 1) {
				iput((*ac)->ac_inode);
				(*ac)->ac_inode = NULL;
				goto retry;
			}

			if (ret < 0)
				mlog_errno(ret);

			inode_lock((*ac)->ac_inode);
			ret = ocfs2_inode_lock((*ac)->ac_inode, NULL, 1);
			if (ret < 0) {
				mlog_errno(ret);
				inode_unlock((*ac)->ac_inode);
				iput((*ac)->ac_inode);
				(*ac)->ac_inode = NULL;
				goto bail;
			}
		}
		if (status < 0) {
			if (status != -ENOSPC)
				mlog_errno(status);
			goto bail;
		}
	}

	status = 0;
bail:
	if ((status < 0) && *ac) {
		ocfs2_free_alloc_context(*ac);
		*ac = NULL;
	}

	if (status)
		mlog_errno(status);
	return status;
}