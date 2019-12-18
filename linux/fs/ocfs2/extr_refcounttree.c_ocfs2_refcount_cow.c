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
typedef  scalar_t__ u32 ;
struct inode {int dummy; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 unsigned int OCFS2_EXT_REFCOUNTED ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_get_clusters (struct inode*,scalar_t__,scalar_t__*,scalar_t__*,unsigned int*) ; 
 int ocfs2_refcount_cow_hunk (struct inode*,struct buffer_head*,scalar_t__,scalar_t__,scalar_t__) ; 

int ocfs2_refcount_cow(struct inode *inode,
		       struct buffer_head *di_bh,
		       u32 cpos, u32 write_len, u32 max_cpos)
{
	int ret = 0;
	u32 p_cluster, num_clusters;
	unsigned int ext_flags;

	while (write_len) {
		ret = ocfs2_get_clusters(inode, cpos, &p_cluster,
					 &num_clusters, &ext_flags);
		if (ret) {
			mlog_errno(ret);
			break;
		}

		if (write_len < num_clusters)
			num_clusters = write_len;

		if (ext_flags & OCFS2_EXT_REFCOUNTED) {
			ret = ocfs2_refcount_cow_hunk(inode, di_bh, cpos,
						      num_clusters, max_cpos);
			if (ret) {
				mlog_errno(ret);
				break;
			}
		}

		write_len -= num_clusters;
		cpos += num_clusters;
	}

	return ret;
}