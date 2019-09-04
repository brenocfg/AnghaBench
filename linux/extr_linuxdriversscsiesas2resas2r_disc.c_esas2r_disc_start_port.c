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
struct esas2r_request {int /*<<< orphan*/  req_stat; struct esas2r_disc_context* interrupt_cx; } ;
struct esas2r_disc_context {int disc_evt; int /*<<< orphan*/  state; int /*<<< orphan*/  flags; } ;
struct esas2r_adapter {scalar_t__ disc_wait_time; int /*<<< orphan*/  flags; struct esas2r_disc_context disc_ctx; struct esas2r_request general_req; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_DISC_IN_PROG ; 
 int /*<<< orphan*/  AF_DISC_POLLED ; 
 int /*<<< orphan*/  AF_PORT_CHANGE ; 
 int DCDE_DEV_CHANGE ; 
 int DCDE_DEV_SCAN ; 
 int /*<<< orphan*/  DCF_DEV_CHANGE ; 
 int /*<<< orphan*/  DCF_DEV_SCAN ; 
 int /*<<< orphan*/  DCF_POLLED ; 
 int /*<<< orphan*/  DCS_BLOCK_DEV_SCAN ; 
 int /*<<< orphan*/  DCS_DEV_RMV ; 
 int /*<<< orphan*/  RS_SUCCESS ; 
 int esas2r_disc_continue (struct esas2r_adapter*,struct esas2r_request*) ; 
 int /*<<< orphan*/  esas2r_hdebug (char*) ; 
 int /*<<< orphan*/  esas2r_trace (char*,int) ; 
 int /*<<< orphan*/  esas2r_trace_enter () ; 
 int /*<<< orphan*/  esas2r_trace_exit () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

bool esas2r_disc_start_port(struct esas2r_adapter *a)
{
	struct esas2r_request *rq = &a->general_req;
	struct esas2r_disc_context *dc = &a->disc_ctx;
	bool ret;

	esas2r_trace_enter();

	if (test_bit(AF_DISC_IN_PROG, &a->flags)) {
		esas2r_trace_exit();

		return false;
	}

	/* If there is a discovery waiting, process it. */
	if (dc->disc_evt) {
		if (test_bit(AF_DISC_POLLED, &a->flags)
		    && a->disc_wait_time == 0) {
			/*
			 * We are doing polled discovery, but we no longer want
			 * to wait for devices.  Stop polled discovery and
			 * transition to interrupt driven discovery.
			 */

			esas2r_trace_exit();

			return false;
		}
	} else {
		/* Discovery is complete. */

		esas2r_hdebug("disc done");

		set_bit(AF_PORT_CHANGE, &a->flags);

		esas2r_trace_exit();

		return false;
	}

	/* Handle the discovery context */
	esas2r_trace("disc_evt: %d", dc->disc_evt);
	set_bit(AF_DISC_IN_PROG, &a->flags);
	dc->flags = 0;

	if (test_bit(AF_DISC_POLLED, &a->flags))
		dc->flags |= DCF_POLLED;

	rq->interrupt_cx = dc;
	rq->req_stat = RS_SUCCESS;

	/* Decode the event code */
	if (dc->disc_evt & DCDE_DEV_SCAN) {
		dc->disc_evt &= ~DCDE_DEV_SCAN;

		dc->flags |= DCF_DEV_SCAN;
		dc->state = DCS_BLOCK_DEV_SCAN;
	} else if (dc->disc_evt & DCDE_DEV_CHANGE) {
		dc->disc_evt &= ~DCDE_DEV_CHANGE;

		dc->flags |= DCF_DEV_CHANGE;
		dc->state = DCS_DEV_RMV;
	}

	/* Continue interrupt driven discovery */
	if (!test_bit(AF_DISC_POLLED, &a->flags))
		ret = esas2r_disc_continue(a, rq);
	else
		ret = true;

	esas2r_trace_exit();

	return ret;
}