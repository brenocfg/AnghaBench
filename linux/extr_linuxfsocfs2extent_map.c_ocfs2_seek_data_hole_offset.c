#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
typedef  int u16 ;
struct ocfs2_extent_rec {unsigned long long e_blkno; int e_flags; int /*<<< orphan*/  e_cpos; int /*<<< orphan*/  e_leaf_clusters; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct file {TYPE_1__* f_mapping; } ;
struct buffer_head {int dummy; } ;
typedef  int loff_t ;
struct TYPE_6__ {int ip_dyn_features; int /*<<< orphan*/  ip_alloc_sem; } ;
struct TYPE_5__ {int s_clustersize_bits; } ;
struct TYPE_4__ {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENXIO ; 
 int OCFS2_EXT_UNWRITTEN ; 
 TYPE_3__* OCFS2_I (struct inode*) ; 
 int OCFS2_INLINE_DATA_FL ; 
 TYPE_2__* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int SEEK_DATA ; 
 int SEEK_HOLE ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int i_size_read (struct inode*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_clusters_for_bytes (int /*<<< orphan*/ ,int) ; 
 int ocfs2_get_clusters_nocache (struct inode*,struct buffer_head*,int,int*,struct ocfs2_extent_rec*,unsigned int*) ; 
 int ocfs2_inode_lock (struct inode*,struct buffer_head**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_inode_unlock (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int ocfs2_seek_data_hole_offset(struct file *file, loff_t *offset, int whence)
{
	struct inode *inode = file->f_mapping->host;
	int ret;
	unsigned int is_last = 0, is_data = 0;
	u16 cs_bits = OCFS2_SB(inode->i_sb)->s_clustersize_bits;
	u32 cpos, cend, clen, hole_size;
	u64 extoff, extlen;
	struct buffer_head *di_bh = NULL;
	struct ocfs2_extent_rec rec;

	BUG_ON(whence != SEEK_DATA && whence != SEEK_HOLE);

	ret = ocfs2_inode_lock(inode, &di_bh, 0);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	down_read(&OCFS2_I(inode)->ip_alloc_sem);

	if (*offset >= i_size_read(inode)) {
		ret = -ENXIO;
		goto out_unlock;
	}

	if (OCFS2_I(inode)->ip_dyn_features & OCFS2_INLINE_DATA_FL) {
		if (whence == SEEK_HOLE)
			*offset = i_size_read(inode);
		goto out_unlock;
	}

	clen = 0;
	cpos = *offset >> cs_bits;
	cend = ocfs2_clusters_for_bytes(inode->i_sb, i_size_read(inode));

	while (cpos < cend && !is_last) {
		ret = ocfs2_get_clusters_nocache(inode, di_bh, cpos, &hole_size,
						 &rec, &is_last);
		if (ret) {
			mlog_errno(ret);
			goto out_unlock;
		}

		extoff = cpos;
		extoff <<= cs_bits;

		if (rec.e_blkno == 0ULL) {
			clen = hole_size;
			is_data = 0;
		} else {
			clen = le16_to_cpu(rec.e_leaf_clusters) -
				(cpos - le32_to_cpu(rec.e_cpos));
			is_data = (rec.e_flags & OCFS2_EXT_UNWRITTEN) ?  0 : 1;
		}

		if ((!is_data && whence == SEEK_HOLE) ||
		    (is_data && whence == SEEK_DATA)) {
			if (extoff > *offset)
				*offset = extoff;
			goto out_unlock;
		}

		if (!is_last)
			cpos += clen;
	}

	if (whence == SEEK_HOLE) {
		extoff = cpos;
		extoff <<= cs_bits;
		extlen = clen;
		extlen <<=  cs_bits;

		if ((extoff + extlen) > i_size_read(inode))
			extlen = i_size_read(inode) - extoff;
		extoff += extlen;
		if (extoff > *offset)
			*offset = extoff;
		goto out_unlock;
	}

	ret = -ENXIO;

out_unlock:

	brelse(di_bh);

	up_read(&OCFS2_I(inode)->ip_alloc_sem);

	ocfs2_inode_unlock(inode, 0);
out:
	return ret;
}