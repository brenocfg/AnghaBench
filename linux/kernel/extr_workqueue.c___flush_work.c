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
struct wq_barrier {int /*<<< orphan*/  work; int /*<<< orphan*/  done; } ;
struct work_struct {int /*<<< orphan*/  lockdep_map; int /*<<< orphan*/  func; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  destroy_work_on_stack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_map_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_map_release (int /*<<< orphan*/ *) ; 
 scalar_t__ start_flush_work (struct work_struct*,struct wq_barrier*,int) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wq_online ; 

__attribute__((used)) static bool __flush_work(struct work_struct *work, bool from_cancel)
{
	struct wq_barrier barr;

	if (WARN_ON(!wq_online))
		return false;

	if (WARN_ON(!work->func))
		return false;

	if (!from_cancel) {
		lock_map_acquire(&work->lockdep_map);
		lock_map_release(&work->lockdep_map);
	}

	if (start_flush_work(work, &barr, from_cancel)) {
		wait_for_completion(&barr.done);
		destroy_work_on_stack(&barr.work);
		return true;
	} else {
		return false;
	}
}