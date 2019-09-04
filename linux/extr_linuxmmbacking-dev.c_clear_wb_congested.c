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
typedef  int /*<<< orphan*/  wait_queue_head_t ;
struct bdi_writeback_congested {int /*<<< orphan*/  state; } ;
typedef  enum wb_congested_state { ____Placeholder_wb_congested_state } wb_congested_state ;

/* Variables and functions */
 int WB_async_congested ; 
 int WB_sync_congested ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * congestion_wqh ; 
 int /*<<< orphan*/ * nr_wb_congested ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 scalar_t__ test_and_clear_bit (int,int /*<<< orphan*/ *) ; 
 scalar_t__ waitqueue_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void clear_wb_congested(struct bdi_writeback_congested *congested, int sync)
{
	wait_queue_head_t *wqh = &congestion_wqh[sync];
	enum wb_congested_state bit;

	bit = sync ? WB_sync_congested : WB_async_congested;
	if (test_and_clear_bit(bit, &congested->state))
		atomic_dec(&nr_wb_congested[sync]);
	smp_mb__after_atomic();
	if (waitqueue_active(wqh))
		wake_up(wqh);
}