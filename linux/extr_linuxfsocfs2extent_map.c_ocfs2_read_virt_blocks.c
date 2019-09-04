#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct inode {TYPE_1__* i_sb; } ;
struct buffer_head {int b_blocknr; } ;
struct TYPE_4__ {scalar_t__ ip_blkno; int /*<<< orphan*/  ip_alloc_sem; } ;
struct TYPE_3__ {int s_blocksize_bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EIO ; 
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int OCFS2_BH_READAHEAD ; 
 TYPE_2__* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int i_size_read (struct inode*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_extent_map_get_blocks (struct inode*,int,int*,int*,int /*<<< orphan*/ *) ; 
 int ocfs2_read_blocks (int /*<<< orphan*/ ,int,int,struct buffer_head**,int,int (*) (struct super_block*,struct buffer_head*)) ; 
 int /*<<< orphan*/  trace_ocfs2_read_virt_blocks (struct inode*,unsigned long long,int,struct buffer_head**,int,int (*) (struct super_block*,struct buffer_head*)) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int ocfs2_read_virt_blocks(struct inode *inode, u64 v_block, int nr,
			   struct buffer_head *bhs[], int flags,
			   int (*validate)(struct super_block *sb,
					   struct buffer_head *bh))
{
	int rc = 0;
	u64 p_block, p_count;
	int i, count, done = 0;

	trace_ocfs2_read_virt_blocks(
	     inode, (unsigned long long)v_block, nr, bhs, flags,
	     validate);

	if (((v_block + nr - 1) << inode->i_sb->s_blocksize_bits) >=
	    i_size_read(inode)) {
		BUG_ON(!(flags & OCFS2_BH_READAHEAD));
		goto out;
	}

	while (done < nr) {
		down_read(&OCFS2_I(inode)->ip_alloc_sem);
		rc = ocfs2_extent_map_get_blocks(inode, v_block + done,
						 &p_block, &p_count, NULL);
		up_read(&OCFS2_I(inode)->ip_alloc_sem);
		if (rc) {
			mlog_errno(rc);
			break;
		}

		if (!p_block) {
			rc = -EIO;
			mlog(ML_ERROR,
			     "Inode #%llu contains a hole at offset %llu\n",
			     (unsigned long long)OCFS2_I(inode)->ip_blkno,
			     (unsigned long long)(v_block + done) <<
			     inode->i_sb->s_blocksize_bits);
			break;
		}

		count = nr - done;
		if (p_count < count)
			count = p_count;

		/*
		 * If the caller passed us bhs, they should have come
		 * from a previous readahead call to this function.  Thus,
		 * they should have the right b_blocknr.
		 */
		for (i = 0; i < count; i++) {
			if (!bhs[done + i])
				continue;
			BUG_ON(bhs[done + i]->b_blocknr != (p_block + i));
		}

		rc = ocfs2_read_blocks(INODE_CACHE(inode), p_block, count,
				       bhs + done, flags, validate);
		if (rc) {
			mlog_errno(rc);
			break;
		}
		done += count;
	}

out:
	return rc;
}