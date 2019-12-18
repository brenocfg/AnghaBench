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
typedef  scalar_t__ u64 ;
struct ocfs2_super {int /*<<< orphan*/  sb; } ;
struct buffer_head {int /*<<< orphan*/  b_end_io; scalar_t__ b_blocknr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int /*<<< orphan*/  REQ_OP_READ ; 
 scalar_t__ buffer_dirty (struct buffer_head*) ; 
 scalar_t__ buffer_jbd (struct buffer_head*) ; 
 scalar_t__ buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  end_buffer_read_sync ; 
 int /*<<< orphan*/  get_bh (struct buffer_head*) ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned long long) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  put_bh (struct buffer_head*) ; 
 struct buffer_head* sb_getblk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  submit_bh (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct buffer_head*) ; 
 int /*<<< orphan*/  trace_ocfs2_read_blocks_sync (unsigned long long,unsigned int) ; 
 int /*<<< orphan*/  trace_ocfs2_read_blocks_sync_jbd (unsigned long long) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  wait_on_buffer (struct buffer_head*) ; 

int ocfs2_read_blocks_sync(struct ocfs2_super *osb, u64 block,
			   unsigned int nr, struct buffer_head *bhs[])
{
	int status = 0;
	unsigned int i;
	struct buffer_head *bh;
	int new_bh = 0;

	trace_ocfs2_read_blocks_sync((unsigned long long)block, nr);

	if (!nr)
		goto bail;

	/* Don't put buffer head and re-assign it to NULL if it is allocated
	 * outside since the caller can't be aware of this alternation!
	 */
	new_bh = (bhs[0] == NULL);

	for (i = 0 ; i < nr ; i++) {
		if (bhs[i] == NULL) {
			bhs[i] = sb_getblk(osb->sb, block++);
			if (bhs[i] == NULL) {
				status = -ENOMEM;
				mlog_errno(status);
				break;
			}
		}
		bh = bhs[i];

		if (buffer_jbd(bh)) {
			trace_ocfs2_read_blocks_sync_jbd(
					(unsigned long long)bh->b_blocknr);
			continue;
		}

		if (buffer_dirty(bh)) {
			/* This should probably be a BUG, or
			 * at least return an error. */
			mlog(ML_ERROR,
			     "trying to sync read a dirty "
			     "buffer! (blocknr = %llu), skipping\n",
			     (unsigned long long)bh->b_blocknr);
			continue;
		}

		lock_buffer(bh);
		if (buffer_jbd(bh)) {
#ifdef CATCH_BH_JBD_RACES
			mlog(ML_ERROR,
			     "block %llu had the JBD bit set "
			     "while I was in lock_buffer!",
			     (unsigned long long)bh->b_blocknr);
			BUG();
#else
			unlock_buffer(bh);
			continue;
#endif
		}

		get_bh(bh); /* for end_buffer_read_sync() */
		bh->b_end_io = end_buffer_read_sync;
		submit_bh(REQ_OP_READ, 0, bh);
	}

read_failure:
	for (i = nr; i > 0; i--) {
		bh = bhs[i - 1];

		if (unlikely(status)) {
			if (new_bh && bh) {
				/* If middle bh fails, let previous bh
				 * finish its read and then put it to
				 * aovoid bh leak
				 */
				if (!buffer_jbd(bh))
					wait_on_buffer(bh);
				put_bh(bh);
				bhs[i - 1] = NULL;
			} else if (bh && buffer_uptodate(bh)) {
				clear_buffer_uptodate(bh);
			}
			continue;
		}

		/* No need to wait on the buffer if it's managed by JBD. */
		if (!buffer_jbd(bh))
			wait_on_buffer(bh);

		if (!buffer_uptodate(bh)) {
			/* Status won't be cleared from here on out,
			 * so we can safely record this and loop back
			 * to cleanup the other buffers. */
			status = -EIO;
			goto read_failure;
		}
	}

bail:
	return status;
}