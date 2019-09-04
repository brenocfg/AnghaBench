#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nvmet_sq {TYPE_1__* ctrl; int /*<<< orphan*/  ref; int /*<<< orphan*/  free_done; int /*<<< orphan*/  confirm_done; } ;
struct TYPE_3__ {struct nvmet_sq** sqs; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvmet_async_events_free (TYPE_1__*) ; 
 int /*<<< orphan*/  nvmet_confirm_sq ; 
 int /*<<< orphan*/  nvmet_ctrl_put (TYPE_1__*) ; 
 int /*<<< orphan*/  percpu_ref_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  percpu_ref_kill_and_confirm (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

void nvmet_sq_destroy(struct nvmet_sq *sq)
{
	/*
	 * If this is the admin queue, complete all AERs so that our
	 * queue doesn't have outstanding requests on it.
	 */
	if (sq->ctrl && sq->ctrl->sqs && sq->ctrl->sqs[0] == sq)
		nvmet_async_events_free(sq->ctrl);
	percpu_ref_kill_and_confirm(&sq->ref, nvmet_confirm_sq);
	wait_for_completion(&sq->confirm_done);
	wait_for_completion(&sq->free_done);
	percpu_ref_exit(&sq->ref);

	if (sq->ctrl) {
		nvmet_ctrl_put(sq->ctrl);
		sq->ctrl = NULL; /* allows reusing the queue later */
	}
}