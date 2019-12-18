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
struct btrfs_work {int /*<<< orphan*/  flags; int /*<<< orphan*/  (* func ) (struct btrfs_work*) ;struct __btrfs_workqueue* wq; scalar_t__ ordered_func; } ;
struct __btrfs_workqueue {int /*<<< orphan*/  fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  WORK_DONE_BIT ; 
 int /*<<< orphan*/  run_ordered_work (struct __btrfs_workqueue*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct btrfs_work*) ; 
 int /*<<< orphan*/  thresh_exec_hook (struct __btrfs_workqueue*) ; 
 int /*<<< orphan*/  trace_btrfs_all_work_done (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  trace_btrfs_work_sched (struct btrfs_work*) ; 

__attribute__((used)) static void normal_work_helper(struct btrfs_work *work)
{
	struct __btrfs_workqueue *wq;
	void *wtag;
	int need_order = 0;

	/*
	 * We should not touch things inside work in the following cases:
	 * 1) after work->func() if it has no ordered_free
	 *    Since the struct is freed in work->func().
	 * 2) after setting WORK_DONE_BIT
	 *    The work may be freed in other threads almost instantly.
	 * So we save the needed things here.
	 */
	if (work->ordered_func)
		need_order = 1;
	wq = work->wq;
	/* Safe for tracepoints in case work gets freed by the callback */
	wtag = work;

	trace_btrfs_work_sched(work);
	thresh_exec_hook(wq);
	work->func(work);
	if (need_order) {
		set_bit(WORK_DONE_BIT, &work->flags);
		run_ordered_work(wq);
	}
	if (!need_order)
		trace_btrfs_all_work_done(wq->fs_info, wtag);
}