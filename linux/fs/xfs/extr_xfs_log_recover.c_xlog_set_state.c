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
typedef  scalar_t__ xfs_daddr_t ;
struct xlog_rec_header {int /*<<< orphan*/  h_lsn; int /*<<< orphan*/  h_tail_lsn; int /*<<< orphan*/  h_cycle; } ;
struct TYPE_4__ {int /*<<< orphan*/  grant; } ;
struct TYPE_3__ {int /*<<< orphan*/  grant; } ;
struct xlog {int l_curr_block; int /*<<< orphan*/  l_curr_cycle; TYPE_2__ l_write_head; TYPE_1__ l_reserve_head; int /*<<< orphan*/  l_last_sync_lsn; int /*<<< orphan*/  l_tail_lsn; scalar_t__ l_prev_block; } ;

/* Variables and functions */
 int /*<<< orphan*/  BBTOB (int) ; 
 int /*<<< orphan*/  atomic64_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xlog_assign_grant_head (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xlog_set_state(
	struct xlog		*log,
	xfs_daddr_t		head_blk,
	struct xlog_rec_header	*rhead,
	xfs_daddr_t		rhead_blk,
	bool			bump_cycle)
{
	/*
	 * Reset log values according to the state of the log when we
	 * crashed.  In the case where head_blk == 0, we bump curr_cycle
	 * one because the next write starts a new cycle rather than
	 * continuing the cycle of the last good log record.  At this
	 * point we have guaranteed that all partial log records have been
	 * accounted for.  Therefore, we know that the last good log record
	 * written was complete and ended exactly on the end boundary
	 * of the physical log.
	 */
	log->l_prev_block = rhead_blk;
	log->l_curr_block = (int)head_blk;
	log->l_curr_cycle = be32_to_cpu(rhead->h_cycle);
	if (bump_cycle)
		log->l_curr_cycle++;
	atomic64_set(&log->l_tail_lsn, be64_to_cpu(rhead->h_tail_lsn));
	atomic64_set(&log->l_last_sync_lsn, be64_to_cpu(rhead->h_lsn));
	xlog_assign_grant_head(&log->l_reserve_head.grant, log->l_curr_cycle,
					BBTOB(log->l_curr_block));
	xlog_assign_grant_head(&log->l_write_head.grant, log->l_curr_cycle,
					BBTOB(log->l_curr_block));
}