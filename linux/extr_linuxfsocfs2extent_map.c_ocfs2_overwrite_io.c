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
typedef  int u64 ;
typedef  int u32 ;
struct ocfs2_super {int s_clustersize_bits; } ;
struct ocfs2_extent_rec {unsigned long long e_blkno; int e_flags; int /*<<< orphan*/  e_leaf_clusters; int /*<<< orphan*/  e_cpos; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct buffer_head {int dummy; } ;
struct TYPE_2__ {int ip_dyn_features; } ;

/* Variables and functions */
 int EAGAIN ; 
 int OCFS2_EXT_REFCOUNTED ; 
 TYPE_1__* OCFS2_I (struct inode*) ; 
 int OCFS2_INLINE_DATA_FL ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_clusters_for_bytes (int /*<<< orphan*/ ,int) ; 
 int ocfs2_get_clusters_nocache (struct inode*,struct buffer_head*,int,int /*<<< orphan*/ *,struct ocfs2_extent_rec*,int*) ; 
 scalar_t__ ocfs2_size_fits_inline_data (struct buffer_head*,int) ; 

int ocfs2_overwrite_io(struct inode *inode, struct buffer_head *di_bh,
		       u64 map_start, u64 map_len)
{
	int ret = 0, is_last;
	u32 mapping_end, cpos;
	struct ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	struct ocfs2_extent_rec rec;

	if (OCFS2_I(inode)->ip_dyn_features & OCFS2_INLINE_DATA_FL) {
		if (ocfs2_size_fits_inline_data(di_bh, map_start + map_len))
			return ret;
		else
			return -EAGAIN;
	}

	cpos = map_start >> osb->s_clustersize_bits;
	mapping_end = ocfs2_clusters_for_bytes(inode->i_sb,
					       map_start + map_len);
	is_last = 0;
	while (cpos < mapping_end && !is_last) {
		ret = ocfs2_get_clusters_nocache(inode, di_bh, cpos,
						 NULL, &rec, &is_last);
		if (ret) {
			mlog_errno(ret);
			goto out;
		}

		if (rec.e_blkno == 0ULL)
			break;

		if (rec.e_flags & OCFS2_EXT_REFCOUNTED)
			break;

		cpos = le32_to_cpu(rec.e_cpos) +
			le16_to_cpu(rec.e_leaf_clusters);
	}

	if (cpos < mapping_end)
		ret = -EAGAIN;
out:
	return ret;
}