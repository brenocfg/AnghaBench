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
typedef  scalar_t__ xfs_daddr_t ;
struct xlog_rec_header {int /*<<< orphan*/  h_num_logops; int /*<<< orphan*/  h_len; int /*<<< orphan*/  h_version; int /*<<< orphan*/  h_size; } ;
struct xlog_op_header {int oh_flags; } ;
struct xlog {int /*<<< orphan*/  l_curr_cycle; int /*<<< orphan*/  l_last_sync_lsn; int /*<<< orphan*/  l_tail_lsn; TYPE_1__* l_mp; } ;
struct TYPE_2__ {int /*<<< orphan*/  m_sb; } ;

/* Variables and functions */
 scalar_t__ BTOBB (int) ; 
 int XLOG_HEADER_CYCLE_SIZE ; 
 int XLOG_UNMOUNT_TRANS ; 
 int XLOG_VERSION_2 ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ xfs_sb_version_haslogv2 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xlog_assign_atomic_lsn (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int xlog_bread (struct xlog*,scalar_t__,int,char*,char**) ; 
 scalar_t__ xlog_wrap_logbno (struct xlog*,scalar_t__) ; 

__attribute__((used)) static int
xlog_check_unmount_rec(
	struct xlog		*log,
	xfs_daddr_t		*head_blk,
	xfs_daddr_t		*tail_blk,
	struct xlog_rec_header	*rhead,
	xfs_daddr_t		rhead_blk,
	char			*buffer,
	bool			*clean)
{
	struct xlog_op_header	*op_head;
	xfs_daddr_t		umount_data_blk;
	xfs_daddr_t		after_umount_blk;
	int			hblks;
	int			error;
	char			*offset;

	*clean = false;

	/*
	 * Look for unmount record. If we find it, then we know there was a
	 * clean unmount. Since 'i' could be the last block in the physical
	 * log, we convert to a log block before comparing to the head_blk.
	 *
	 * Save the current tail lsn to use to pass to xlog_clear_stale_blocks()
	 * below. We won't want to clear the unmount record if there is one, so
	 * we pass the lsn of the unmount record rather than the block after it.
	 */
	if (xfs_sb_version_haslogv2(&log->l_mp->m_sb)) {
		int	h_size = be32_to_cpu(rhead->h_size);
		int	h_version = be32_to_cpu(rhead->h_version);

		if ((h_version & XLOG_VERSION_2) &&
		    (h_size > XLOG_HEADER_CYCLE_SIZE)) {
			hblks = h_size / XLOG_HEADER_CYCLE_SIZE;
			if (h_size % XLOG_HEADER_CYCLE_SIZE)
				hblks++;
		} else {
			hblks = 1;
		}
	} else {
		hblks = 1;
	}

	after_umount_blk = xlog_wrap_logbno(log,
			rhead_blk + hblks + BTOBB(be32_to_cpu(rhead->h_len)));

	if (*head_blk == after_umount_blk &&
	    be32_to_cpu(rhead->h_num_logops) == 1) {
		umount_data_blk = xlog_wrap_logbno(log, rhead_blk + hblks);
		error = xlog_bread(log, umount_data_blk, 1, buffer, &offset);
		if (error)
			return error;

		op_head = (struct xlog_op_header *)offset;
		if (op_head->oh_flags & XLOG_UNMOUNT_TRANS) {
			/*
			 * Set tail and last sync so that newly written log
			 * records will point recovery to after the current
			 * unmount record.
			 */
			xlog_assign_atomic_lsn(&log->l_tail_lsn,
					log->l_curr_cycle, after_umount_blk);
			xlog_assign_atomic_lsn(&log->l_last_sync_lsn,
					log->l_curr_cycle, after_umount_blk);
			*tail_blk = after_umount_blk;

			*clean = true;
		}
	}

	return 0;
}