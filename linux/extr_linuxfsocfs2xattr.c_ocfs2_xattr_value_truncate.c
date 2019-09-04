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
typedef  scalar_t__ u32 ;
struct ocfs2_xattr_value_buf {TYPE_1__* vb_xv; } ;
struct ocfs2_xattr_set_ctxt {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct TYPE_2__ {int /*<<< orphan*/  xr_clusters; } ;

/* Variables and functions */
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ ocfs2_clusters_for_bytes (int /*<<< orphan*/ ,int) ; 
 int ocfs2_xattr_extend_allocation (struct inode*,scalar_t__,struct ocfs2_xattr_value_buf*,struct ocfs2_xattr_set_ctxt*) ; 
 int ocfs2_xattr_shrink_size (struct inode*,scalar_t__,scalar_t__,struct ocfs2_xattr_value_buf*,struct ocfs2_xattr_set_ctxt*) ; 

__attribute__((used)) static int ocfs2_xattr_value_truncate(struct inode *inode,
				      struct ocfs2_xattr_value_buf *vb,
				      int len,
				      struct ocfs2_xattr_set_ctxt *ctxt)
{
	int ret;
	u32 new_clusters = ocfs2_clusters_for_bytes(inode->i_sb, len);
	u32 old_clusters = le32_to_cpu(vb->vb_xv->xr_clusters);

	if (new_clusters == old_clusters)
		return 0;

	if (new_clusters > old_clusters)
		ret = ocfs2_xattr_extend_allocation(inode,
						    new_clusters - old_clusters,
						    vb, ctxt);
	else
		ret = ocfs2_xattr_shrink_size(inode,
					      old_clusters, new_clusters,
					      vb, ctxt);

	return ret;
}