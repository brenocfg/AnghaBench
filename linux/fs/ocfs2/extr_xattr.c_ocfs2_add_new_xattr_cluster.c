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
typedef  scalar_t__ u64 ;
typedef  int u32 ;
typedef  int u16 ;
struct ocfs2_xattr_set_ctxt {int /*<<< orphan*/  meta_ac; int /*<<< orphan*/  data_ac; int /*<<< orphan*/ * handle; } ;
struct ocfs2_xattr_bucket {int dummy; } ;
struct ocfs2_super {scalar_t__ s_clustersize_bits; int /*<<< orphan*/  sb; } ;
struct ocfs2_extent_tree {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_2__ {scalar_t__ ip_blkno; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOSPC ; 
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 TYPE_1__* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_WRITE ; 
 scalar_t__ OCFS2_MAX_XATTR_TREE_LEAF_SIZE ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int __ocfs2_claim_clusters (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int*,int*) ; 
 scalar_t__ bucket_blkno (struct ocfs2_xattr_bucket*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_adjust_xattr_cross_cluster (struct inode*,int /*<<< orphan*/ *,struct ocfs2_xattr_bucket*,struct ocfs2_xattr_bucket*,scalar_t__,int,int*,int*) ; 
 void* ocfs2_clusters_to_blocks (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ocfs2_init_xattr_tree_extent_tree (struct ocfs2_extent_tree*,int /*<<< orphan*/ ,struct buffer_head*) ; 
 int ocfs2_insert_extent (int /*<<< orphan*/ *,struct ocfs2_extent_tree*,int,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ocfs2_journal_access_xb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_journal_dirty (int /*<<< orphan*/ *,struct buffer_head*) ; 
 int /*<<< orphan*/  trace_ocfs2_add_new_xattr_cluster (unsigned long long,int) ; 
 int /*<<< orphan*/  trace_ocfs2_add_new_xattr_cluster_begin (unsigned long long,unsigned long long,int,int) ; 
 int /*<<< orphan*/  trace_ocfs2_add_new_xattr_cluster_insert (unsigned long long,int,int) ; 

__attribute__((used)) static int ocfs2_add_new_xattr_cluster(struct inode *inode,
				       struct buffer_head *root_bh,
				       struct ocfs2_xattr_bucket *first,
				       struct ocfs2_xattr_bucket *target,
				       u32 *num_clusters,
				       u32 prev_cpos,
				       int *extend,
				       struct ocfs2_xattr_set_ctxt *ctxt)
{
	int ret;
	u16 bpc = ocfs2_clusters_to_blocks(inode->i_sb, 1);
	u32 prev_clusters = *num_clusters;
	u32 clusters_to_add = 1, bit_off, num_bits, v_start = 0;
	u64 block;
	handle_t *handle = ctxt->handle;
	struct ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	struct ocfs2_extent_tree et;

	trace_ocfs2_add_new_xattr_cluster_begin(
		(unsigned long long)OCFS2_I(inode)->ip_blkno,
		(unsigned long long)bucket_blkno(first),
		prev_cpos, prev_clusters);

	ocfs2_init_xattr_tree_extent_tree(&et, INODE_CACHE(inode), root_bh);

	ret = ocfs2_journal_access_xb(handle, INODE_CACHE(inode), root_bh,
				      OCFS2_JOURNAL_ACCESS_WRITE);
	if (ret < 0) {
		mlog_errno(ret);
		goto leave;
	}

	ret = __ocfs2_claim_clusters(handle, ctxt->data_ac, 1,
				     clusters_to_add, &bit_off, &num_bits);
	if (ret < 0) {
		if (ret != -ENOSPC)
			mlog_errno(ret);
		goto leave;
	}

	BUG_ON(num_bits > clusters_to_add);

	block = ocfs2_clusters_to_blocks(osb->sb, bit_off);
	trace_ocfs2_add_new_xattr_cluster((unsigned long long)block, num_bits);

	if (bucket_blkno(first) + (prev_clusters * bpc) == block &&
	    (prev_clusters + num_bits) << osb->s_clustersize_bits <=
	     OCFS2_MAX_XATTR_TREE_LEAF_SIZE) {
		/*
		 * If this cluster is contiguous with the old one and
		 * adding this new cluster, we don't surpass the limit of
		 * OCFS2_MAX_XATTR_TREE_LEAF_SIZE, cool. We will let it be
		 * initialized and used like other buckets in the previous
		 * cluster.
		 * So add it as a contiguous one. The caller will handle
		 * its init process.
		 */
		v_start = prev_cpos + prev_clusters;
		*num_clusters = prev_clusters + num_bits;
	} else {
		ret = ocfs2_adjust_xattr_cross_cluster(inode,
						       handle,
						       first,
						       target,
						       block,
						       prev_clusters,
						       &v_start,
						       extend);
		if (ret) {
			mlog_errno(ret);
			goto leave;
		}
	}

	trace_ocfs2_add_new_xattr_cluster_insert((unsigned long long)block,
						 v_start, num_bits);
	ret = ocfs2_insert_extent(handle, &et, v_start, block,
				  num_bits, 0, ctxt->meta_ac);
	if (ret < 0) {
		mlog_errno(ret);
		goto leave;
	}

	ocfs2_journal_dirty(handle, root_bh);

leave:
	return ret;
}