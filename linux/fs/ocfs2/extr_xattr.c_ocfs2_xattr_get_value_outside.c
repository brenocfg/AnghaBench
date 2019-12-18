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
typedef  void* u64 ;
typedef  scalar_t__ u32 ;
struct ocfs2_extent_list {int dummy; } ;
struct ocfs2_xattr_value_root {int /*<<< orphan*/  xr_clusters; struct ocfs2_extent_list xr_list; } ;
struct inode {TYPE_1__* i_sb; } ;
struct buffer_head {int /*<<< orphan*/  b_data; } ;
struct TYPE_2__ {size_t s_blocksize; } ;

/* Variables and functions */
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 void* ocfs2_clusters_to_blocks (TYPE_1__*,scalar_t__) ; 
 int ocfs2_read_block (int /*<<< orphan*/ ,void*,struct buffer_head**,int /*<<< orphan*/ *) ; 
 int ocfs2_xattr_get_clusters (struct inode*,scalar_t__,scalar_t__*,scalar_t__*,struct ocfs2_extent_list*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ocfs2_xattr_get_value_outside(struct inode *inode,
					 struct ocfs2_xattr_value_root *xv,
					 void *buffer,
					 size_t len)
{
	u32 cpos, p_cluster, num_clusters, bpc, clusters;
	u64 blkno;
	int i, ret = 0;
	size_t cplen, blocksize;
	struct buffer_head *bh = NULL;
	struct ocfs2_extent_list *el;

	el = &xv->xr_list;
	clusters = le32_to_cpu(xv->xr_clusters);
	bpc = ocfs2_clusters_to_blocks(inode->i_sb, 1);
	blocksize = inode->i_sb->s_blocksize;

	cpos = 0;
	while (cpos < clusters) {
		ret = ocfs2_xattr_get_clusters(inode, cpos, &p_cluster,
					       &num_clusters, el, NULL);
		if (ret) {
			mlog_errno(ret);
			goto out;
		}

		blkno = ocfs2_clusters_to_blocks(inode->i_sb, p_cluster);
		/* Copy ocfs2_xattr_value */
		for (i = 0; i < num_clusters * bpc; i++, blkno++) {
			ret = ocfs2_read_block(INODE_CACHE(inode), blkno,
					       &bh, NULL);
			if (ret) {
				mlog_errno(ret);
				goto out;
			}

			cplen = len >= blocksize ? blocksize : len;
			memcpy(buffer, bh->b_data, cplen);
			len -= cplen;
			buffer += cplen;

			brelse(bh);
			bh = NULL;
			if (len == 0)
				break;
		}
		cpos += num_clusters;
	}
out:
	return ret;
}