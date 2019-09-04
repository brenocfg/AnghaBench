#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* u64 ;
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct ocfs2_xattr_value_root {int /*<<< orphan*/  xr_list; int /*<<< orphan*/  xr_clusters; } ;
struct ocfs2_xattr_value_buf {struct ocfs2_xattr_value_root* vb_xv; } ;
struct inode {TYPE_1__* i_sb; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_3__ {int s_blocksize; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (unsigned int) ; 
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 unsigned int OCFS2_EXT_REFCOUNTED ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_WRITE ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,void const*,int) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 scalar_t__ ocfs2_clusters_for_bytes (TYPE_1__*,int) ; 
 void* ocfs2_clusters_to_blocks (TYPE_1__*,scalar_t__) ; 
 int ocfs2_journal_access (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_journal_dirty (int /*<<< orphan*/ *,struct buffer_head*) ; 
 int ocfs2_read_block (int /*<<< orphan*/ ,void*,struct buffer_head**,int /*<<< orphan*/ *) ; 
 int ocfs2_xattr_get_clusters (struct inode*,scalar_t__,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,unsigned int*) ; 

__attribute__((used)) static int __ocfs2_xattr_set_value_outside(struct inode *inode,
					   handle_t *handle,
					   struct ocfs2_xattr_value_buf *vb,
					   const void *value,
					   int value_len)
{
	int ret = 0, i, cp_len;
	u16 blocksize = inode->i_sb->s_blocksize;
	u32 p_cluster, num_clusters;
	u32 cpos = 0, bpc = ocfs2_clusters_to_blocks(inode->i_sb, 1);
	u32 clusters = ocfs2_clusters_for_bytes(inode->i_sb, value_len);
	u64 blkno;
	struct buffer_head *bh = NULL;
	unsigned int ext_flags;
	struct ocfs2_xattr_value_root *xv = vb->vb_xv;

	BUG_ON(clusters > le32_to_cpu(xv->xr_clusters));

	while (cpos < clusters) {
		ret = ocfs2_xattr_get_clusters(inode, cpos, &p_cluster,
					       &num_clusters, &xv->xr_list,
					       &ext_flags);
		if (ret) {
			mlog_errno(ret);
			goto out;
		}

		BUG_ON(ext_flags & OCFS2_EXT_REFCOUNTED);

		blkno = ocfs2_clusters_to_blocks(inode->i_sb, p_cluster);

		for (i = 0; i < num_clusters * bpc; i++, blkno++) {
			ret = ocfs2_read_block(INODE_CACHE(inode), blkno,
					       &bh, NULL);
			if (ret) {
				mlog_errno(ret);
				goto out;
			}

			ret = ocfs2_journal_access(handle,
						   INODE_CACHE(inode),
						   bh,
						   OCFS2_JOURNAL_ACCESS_WRITE);
			if (ret < 0) {
				mlog_errno(ret);
				goto out;
			}

			cp_len = value_len > blocksize ? blocksize : value_len;
			memcpy(bh->b_data, value, cp_len);
			value_len -= cp_len;
			value += cp_len;
			if (cp_len < blocksize)
				memset(bh->b_data + cp_len, 0,
				       blocksize - cp_len);

			ocfs2_journal_dirty(handle, bh);
			brelse(bh);
			bh = NULL;

			/*
			 * XXX: do we need to empty all the following
			 * blocks in this cluster?
			 */
			if (!value_len)
				break;
		}
		cpos += num_clusters;
	}
out:
	brelse(bh);

	return ret;
}