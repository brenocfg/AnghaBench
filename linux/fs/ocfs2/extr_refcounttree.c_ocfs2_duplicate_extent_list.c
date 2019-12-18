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
struct ocfs2_extent_tree {int dummy; } ;
struct ocfs2_caching_info {int dummy; } ;
struct ocfs2_cached_dealloc_ctxt {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 int /*<<< orphan*/  i_size_read (struct inode*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_add_refcounted_extent (struct inode*,struct ocfs2_extent_tree*,struct ocfs2_caching_info*,struct buffer_head*,scalar_t__,scalar_t__,scalar_t__,unsigned int,struct ocfs2_cached_dealloc_ctxt*) ; 
 scalar_t__ ocfs2_clusters_for_bytes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ocfs2_get_clusters (struct inode*,scalar_t__,scalar_t__*,scalar_t__*,unsigned int*) ; 
 int /*<<< orphan*/  ocfs2_init_dinode_extent_tree (struct ocfs2_extent_tree*,int /*<<< orphan*/ ,struct buffer_head*) ; 

__attribute__((used)) static int ocfs2_duplicate_extent_list(struct inode *s_inode,
				struct inode *t_inode,
				struct buffer_head *t_bh,
				struct ocfs2_caching_info *ref_ci,
				struct buffer_head *ref_root_bh,
				struct ocfs2_cached_dealloc_ctxt *dealloc)
{
	int ret = 0;
	u32 p_cluster, num_clusters, clusters, cpos;
	loff_t size;
	unsigned int ext_flags;
	struct ocfs2_extent_tree et;

	ocfs2_init_dinode_extent_tree(&et, INODE_CACHE(t_inode), t_bh);

	size = i_size_read(s_inode);
	clusters = ocfs2_clusters_for_bytes(s_inode->i_sb, size);

	cpos = 0;
	while (cpos < clusters) {
		ret = ocfs2_get_clusters(s_inode, cpos, &p_cluster,
					 &num_clusters, &ext_flags);
		if (ret) {
			mlog_errno(ret);
			goto out;
		}
		if (p_cluster) {
			ret = ocfs2_add_refcounted_extent(t_inode, &et,
							  ref_ci, ref_root_bh,
							  cpos, p_cluster,
							  num_clusters,
							  ext_flags,
							  dealloc);
			if (ret) {
				mlog_errno(ret);
				goto out;
			}
		}

		cpos += num_clusters;
	}

out:
	return ret;
}