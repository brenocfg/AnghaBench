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
struct esas2r_request {scalar_t__ req_stat; scalar_t__ timeout; int /*<<< orphan*/ * interrupt_cx; } ;
struct esas2r_adapter {struct esas2r_request general_req; } ;

/* Variables and functions */
 scalar_t__ RQ_MAX_TIMEOUT ; 
 scalar_t__ RS_PENDING ; 
 scalar_t__ RS_STARTED ; 
 scalar_t__ RS_TIMEOUT ; 
 int /*<<< orphan*/  esas2r_disc_abort (struct esas2r_adapter*,struct esas2r_request*) ; 
 int /*<<< orphan*/  esas2r_disc_continue (struct esas2r_adapter*,struct esas2r_request*) ; 
 int /*<<< orphan*/  esas2r_disc_start_waiting (struct esas2r_adapter*) ; 
 int /*<<< orphan*/  esas2r_local_reset_adapter (struct esas2r_adapter*) ; 
 int /*<<< orphan*/  esas2r_polled_interrupt (struct esas2r_adapter*) ; 
 int /*<<< orphan*/  esas2r_wait_request (struct esas2r_adapter*,struct esas2r_request*) ; 

void esas2r_disc_check_for_work(struct esas2r_adapter *a)
{
	struct esas2r_request *rq = &a->general_req;

	/* service any pending interrupts first */

	esas2r_polled_interrupt(a);

	/*
	 * now, interrupt processing may have queued up a discovery event.  go
	 * see if we have one to start.  we couldn't start it in the ISR since
	 * polled discovery would cause a deadlock.
	 */

	esas2r_disc_start_waiting(a);

	if (rq->interrupt_cx == NULL)
		return;

	if (rq->req_stat == RS_STARTED
	    && rq->timeout <= RQ_MAX_TIMEOUT) {
		/* wait for the current discovery request to complete. */
		esas2r_wait_request(a, rq);

		if (rq->req_stat == RS_TIMEOUT) {
			esas2r_disc_abort(a, rq);
			esas2r_local_reset_adapter(a);
			return;
		}
	}

	if (rq->req_stat == RS_PENDING
	    || rq->req_stat == RS_STARTED)
		return;

	esas2r_disc_continue(a, rq);
}