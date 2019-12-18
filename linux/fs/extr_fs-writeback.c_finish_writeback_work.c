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
struct wb_writeback_work {scalar_t__ auto_free; struct wb_completion* done; } ;
struct wb_completion {int /*<<< orphan*/  cnt; int /*<<< orphan*/ * waitq; } ;
struct bdi_writeback {int dummy; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct wb_writeback_work*) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void finish_writeback_work(struct bdi_writeback *wb,
				  struct wb_writeback_work *work)
{
	struct wb_completion *done = work->done;

	if (work->auto_free)
		kfree(work);
	if (done) {
		wait_queue_head_t *waitq = done->waitq;

		/* @done can't be accessed after the following dec */
		if (atomic_dec_and_test(&done->cnt))
			wake_up_all(waitq);
	}
}