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
struct wb_writeback_work {int /*<<< orphan*/  list; TYPE_1__* done; } ;
struct bdi_writeback {int /*<<< orphan*/  work_lock; int /*<<< orphan*/  dwork; int /*<<< orphan*/  work_list; int /*<<< orphan*/  state; } ;
struct TYPE_2__ {int /*<<< orphan*/  cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  WB_registered ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bdi_wq ; 
 int /*<<< orphan*/  finish_writeback_work (struct bdi_writeback*,struct wb_writeback_work*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mod_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_writeback_queue (struct bdi_writeback*,struct wb_writeback_work*) ; 

__attribute__((used)) static void wb_queue_work(struct bdi_writeback *wb,
			  struct wb_writeback_work *work)
{
	trace_writeback_queue(wb, work);

	if (work->done)
		atomic_inc(&work->done->cnt);

	spin_lock_bh(&wb->work_lock);

	if (test_bit(WB_registered, &wb->state)) {
		list_add_tail(&work->list, &wb->work_list);
		mod_delayed_work(bdi_wq, &wb->dwork, 0);
	} else
		finish_writeback_work(wb, work);

	spin_unlock_bh(&wb->work_lock);
}