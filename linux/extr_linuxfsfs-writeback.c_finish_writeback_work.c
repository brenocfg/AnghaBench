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
struct wb_writeback_work {scalar_t__ auto_free; struct wb_completion* done; } ;
struct wb_completion {int /*<<< orphan*/  cnt; } ;
struct bdi_writeback {TYPE_1__* bdi; } ;
struct TYPE_2__ {int /*<<< orphan*/  wb_waitq; } ;

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
	if (done && atomic_dec_and_test(&done->cnt))
		wake_up_all(&wb->bdi->wb_waitq);
}