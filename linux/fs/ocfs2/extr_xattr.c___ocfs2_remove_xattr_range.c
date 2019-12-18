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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct ocfs2_xattr_value_buf {int (* vb_access ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  vb_bh; TYPE_1__* vb_xv; } ;
struct ocfs2_xattr_set_ctxt {int /*<<< orphan*/  dealloc; int /*<<< orphan*/  meta_ac; int /*<<< orphan*/ * handle; } ;
struct ocfs2_extent_tree {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_2__ {int /*<<< orphan*/  xr_clusters; } ;

/* Variables and functions */
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 unsigned int OCFS2_EXT_REFCOUNTED ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_WRITE ; 
 int /*<<< orphan*/  le32_add_cpu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_blocks_to_clusters (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ocfs2_cache_cluster_dealloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_clusters_to_blocks (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ocfs2_decrease_refcount (struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ocfs2_init_xattr_value_extent_tree (struct ocfs2_extent_tree*,int /*<<< orphan*/ ,struct ocfs2_xattr_value_buf*) ; 
 int /*<<< orphan*/  ocfs2_journal_dirty (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ocfs2_remove_extent (int /*<<< orphan*/ *,struct ocfs2_extent_tree*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __ocfs2_remove_xattr_range(struct inode *inode,
				      struct ocfs2_xattr_value_buf *vb,
				      u32 cpos, u32 phys_cpos, u32 len,
				      unsigned int ext_flags,
				      struct ocfs2_xattr_set_ctxt *ctxt)
{
	int ret;
	u64 phys_blkno = ocfs2_clusters_to_blocks(inode->i_sb, phys_cpos);
	handle_t *handle = ctxt->handle;
	struct ocfs2_extent_tree et;

	ocfs2_init_xattr_value_extent_tree(&et, INODE_CACHE(inode), vb);

	ret = vb->vb_access(handle, INODE_CACHE(inode), vb->vb_bh,
			    OCFS2_JOURNAL_ACCESS_WRITE);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	ret = ocfs2_remove_extent(handle, &et, cpos, len, ctxt->meta_ac,
				  &ctxt->dealloc);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	le32_add_cpu(&vb->vb_xv->xr_clusters, -len);
	ocfs2_journal_dirty(handle, vb->vb_bh);

	if (ext_flags & OCFS2_EXT_REFCOUNTED)
		ret = ocfs2_decrease_refcount(inode, handle,
					ocfs2_blocks_to_clusters(inode->i_sb,
								 phys_blkno),
					len, ctxt->meta_ac, &ctxt->dealloc, 1);
	else
		ret = ocfs2_cache_cluster_dealloc(&ctxt->dealloc,
						  phys_blkno, len);
	if (ret)
		mlog_errno(ret);

out:
	return ret;
}