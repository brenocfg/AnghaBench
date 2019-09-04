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
typedef  int /*<<< orphan*/  u32 ;
struct rsi_common {scalar_t__ coex_cb; } ;
struct TYPE_2__ {int /*<<< orphan*/  completion; int /*<<< orphan*/  event; int /*<<< orphan*/  thread_done; } ;
struct rsi_coex_ctrl_block {TYPE_1__ coex_tx_thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_WAIT_FOREVER ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete_and_exit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsi_coex_sched_tx_pkts (struct rsi_coex_ctrl_block*) ; 
 int /*<<< orphan*/  rsi_reset_event (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rsi_wait_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rsi_coex_scheduler_thread(struct rsi_common *common)
{
	struct rsi_coex_ctrl_block *coex_cb =
		(struct rsi_coex_ctrl_block *)common->coex_cb;
	u32 timeout = EVENT_WAIT_FOREVER;

	do {
		rsi_wait_event(&coex_cb->coex_tx_thread.event, timeout);
		rsi_reset_event(&coex_cb->coex_tx_thread.event);

		rsi_coex_sched_tx_pkts(coex_cb);
	} while (atomic_read(&coex_cb->coex_tx_thread.thread_done) == 0);

	complete_and_exit(&coex_cb->coex_tx_thread.completion, 0);
}