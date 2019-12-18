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
struct ocfs2_super {int dummy; } ;
struct inode {scalar_t__ i_blkbits; int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_ino; } ;
struct buffer_head {scalar_t__ b_size; } ;
typedef  scalar_t__ sector_t ;
struct TYPE_2__ {int ip_flags; scalar_t__ ip_blkno; int /*<<< orphan*/  ip_clusters; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int /*<<< orphan*/  ML_NOTICE ; 
 unsigned int OCFS2_EXT_UNWRITTEN ; 
 TYPE_1__* OCFS2_I (struct inode*) ; 
 int OCFS2_INODE_SYSTEM_FILE ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  dump_stack () ; 
 scalar_t__ i_size_read (struct inode*) ; 
 int /*<<< orphan*/  map_bh (struct buffer_head*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ ocfs2_blocks_for_bytes (int /*<<< orphan*/ ,scalar_t__) ; 
 int ocfs2_extent_map_get_blocks (struct inode*,scalar_t__,scalar_t__*,scalar_t__*,unsigned int*) ; 
 scalar_t__ ocfs2_sparse_alloc (struct ocfs2_super*) ; 
 int ocfs2_symlink_get_block (struct inode*,scalar_t__,struct buffer_head*,int) ; 
 int /*<<< orphan*/  set_buffer_new (struct buffer_head*) ; 
 int /*<<< orphan*/  trace_ocfs2_get_block (unsigned long long,unsigned long long,struct buffer_head*,int) ; 
 int /*<<< orphan*/  trace_ocfs2_get_block_end (unsigned long long,unsigned long long) ; 

int ocfs2_get_block(struct inode *inode, sector_t iblock,
		    struct buffer_head *bh_result, int create)
{
	int err = 0;
	unsigned int ext_flags;
	u64 max_blocks = bh_result->b_size >> inode->i_blkbits;
	u64 p_blkno, count, past_eof;
	struct ocfs2_super *osb = OCFS2_SB(inode->i_sb);

	trace_ocfs2_get_block((unsigned long long)OCFS2_I(inode)->ip_blkno,
			      (unsigned long long)iblock, bh_result, create);

	if (OCFS2_I(inode)->ip_flags & OCFS2_INODE_SYSTEM_FILE)
		mlog(ML_NOTICE, "get_block on system inode 0x%p (%lu)\n",
		     inode, inode->i_ino);

	if (S_ISLNK(inode->i_mode)) {
		/* this always does I/O for some reason. */
		err = ocfs2_symlink_get_block(inode, iblock, bh_result, create);
		goto bail;
	}

	err = ocfs2_extent_map_get_blocks(inode, iblock, &p_blkno, &count,
					  &ext_flags);
	if (err) {
		mlog(ML_ERROR, "Error %d from get_blocks(0x%p, %llu, 1, "
		     "%llu, NULL)\n", err, inode, (unsigned long long)iblock,
		     (unsigned long long)p_blkno);
		goto bail;
	}

	if (max_blocks < count)
		count = max_blocks;

	/*
	 * ocfs2 never allocates in this function - the only time we
	 * need to use BH_New is when we're extending i_size on a file
	 * system which doesn't support holes, in which case BH_New
	 * allows __block_write_begin() to zero.
	 *
	 * If we see this on a sparse file system, then a truncate has
	 * raced us and removed the cluster. In this case, we clear
	 * the buffers dirty and uptodate bits and let the buffer code
	 * ignore it as a hole.
	 */
	if (create && p_blkno == 0 && ocfs2_sparse_alloc(osb)) {
		clear_buffer_dirty(bh_result);
		clear_buffer_uptodate(bh_result);
		goto bail;
	}

	/* Treat the unwritten extent as a hole for zeroing purposes. */
	if (p_blkno && !(ext_flags & OCFS2_EXT_UNWRITTEN))
		map_bh(bh_result, inode->i_sb, p_blkno);

	bh_result->b_size = count << inode->i_blkbits;

	if (!ocfs2_sparse_alloc(osb)) {
		if (p_blkno == 0) {
			err = -EIO;
			mlog(ML_ERROR,
			     "iblock = %llu p_blkno = %llu blkno=(%llu)\n",
			     (unsigned long long)iblock,
			     (unsigned long long)p_blkno,
			     (unsigned long long)OCFS2_I(inode)->ip_blkno);
			mlog(ML_ERROR, "Size %llu, clusters %u\n", (unsigned long long)i_size_read(inode), OCFS2_I(inode)->ip_clusters);
			dump_stack();
			goto bail;
		}
	}

	past_eof = ocfs2_blocks_for_bytes(inode->i_sb, i_size_read(inode));

	trace_ocfs2_get_block_end((unsigned long long)OCFS2_I(inode)->ip_blkno,
				  (unsigned long long)past_eof);
	if (create && (iblock >= past_eof))
		set_buffer_new(bh_result);

bail:
	if (err < 0)
		err = -EIO;

	return err;
}