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
typedef  int /*<<< orphan*/  xfs_lsn_t ;
struct xlog {int l_curr_cycle; int l_curr_block; int /*<<< orphan*/  l_icloglock; } ;

/* Variables and functions */
 int BLOCK_LSN (int /*<<< orphan*/ ) ; 
 int CYCLE_LSN (int /*<<< orphan*/ ) ; 
 int READ_ONCE (int) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool
xlog_valid_lsn(
	struct xlog	*log,
	xfs_lsn_t	lsn)
{
	int		cur_cycle;
	int		cur_block;
	bool		valid = true;

	/*
	 * First, sample the current lsn without locking to avoid added
	 * contention from metadata I/O. The current cycle and block are updated
	 * (in xlog_state_switch_iclogs()) and read here in a particular order
	 * to avoid false negatives (e.g., thinking the metadata LSN is valid
	 * when it is not).
	 *
	 * The current block is always rewound before the cycle is bumped in
	 * xlog_state_switch_iclogs() to ensure the current LSN is never seen in
	 * a transiently forward state. Instead, we can see the LSN in a
	 * transiently behind state if we happen to race with a cycle wrap.
	 */
	cur_cycle = READ_ONCE(log->l_curr_cycle);
	smp_rmb();
	cur_block = READ_ONCE(log->l_curr_block);

	if ((CYCLE_LSN(lsn) > cur_cycle) ||
	    (CYCLE_LSN(lsn) == cur_cycle && BLOCK_LSN(lsn) > cur_block)) {
		/*
		 * If the metadata LSN appears invalid, it's possible the check
		 * above raced with a wrap to the next log cycle. Grab the lock
		 * to check for sure.
		 */
		spin_lock(&log->l_icloglock);
		cur_cycle = log->l_curr_cycle;
		cur_block = log->l_curr_block;
		spin_unlock(&log->l_icloglock);

		if ((CYCLE_LSN(lsn) > cur_cycle) ||
		    (CYCLE_LSN(lsn) == cur_cycle && BLOCK_LSN(lsn) > cur_block))
			valid = false;
	}

	return valid;
}