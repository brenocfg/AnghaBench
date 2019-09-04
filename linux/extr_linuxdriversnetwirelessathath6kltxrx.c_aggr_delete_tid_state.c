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
typedef  size_t u8 ;
struct rxtid_stats {int dummy; } ;
struct rxtid {int aggr; int timer_mon; int /*<<< orphan*/ * hold_q; scalar_t__ hold_q_sz; scalar_t__ seq_next; scalar_t__ win_sz; } ;
struct aggr_info_conn {struct rxtid_stats* stat; struct rxtid* rx_tid; } ;

/* Variables and functions */
 size_t NUM_OF_TIDS ; 
 int /*<<< orphan*/  aggr_deque_frms (struct aggr_info_conn*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct rxtid_stats*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void aggr_delete_tid_state(struct aggr_info_conn *aggr_conn, u8 tid)
{
	struct rxtid *rxtid;
	struct rxtid_stats *stats;

	if (!aggr_conn || tid >= NUM_OF_TIDS)
		return;

	rxtid = &aggr_conn->rx_tid[tid];
	stats = &aggr_conn->stat[tid];

	if (rxtid->aggr)
		aggr_deque_frms(aggr_conn, tid, 0, 0);

	rxtid->aggr = false;
	rxtid->timer_mon = false;
	rxtid->win_sz = 0;
	rxtid->seq_next = 0;
	rxtid->hold_q_sz = 0;

	kfree(rxtid->hold_q);
	rxtid->hold_q = NULL;

	memset(stats, 0, sizeof(struct rxtid_stats));
}