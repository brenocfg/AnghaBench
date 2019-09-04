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
struct esas2r_request {scalar_t__ req_stat; int flags; int /*<<< orphan*/  comp_cb; } ;
struct esas2r_adapter {scalar_t__ init_msg; int /*<<< orphan*/  queue_lock; struct esas2r_request general_req; } ;

/* Variables and functions */
 scalar_t__ ESAS2R_INIT_MSG_REINIT ; 
 scalar_t__ ESAS2R_INIT_MSG_START ; 
 int /*<<< orphan*/  ESAS2R_LOG_CRIT ; 
 int RF_FAILURE_OK ; 
 scalar_t__ RS_PENDING ; 
 scalar_t__ RS_SUCCESS ; 
 scalar_t__ RS_TIMEOUT ; 
 int /*<<< orphan*/  esas2r_dummy_complete ; 
 scalar_t__ esas2r_format_init_msg (struct esas2r_adapter*,struct esas2r_request*) ; 
 int /*<<< orphan*/  esas2r_log (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  esas2r_rq_destroy_request (struct esas2r_request*,struct esas2r_adapter*) ; 
 int /*<<< orphan*/  esas2r_rq_init_request (struct esas2r_request*,struct esas2r_adapter*) ; 
 int /*<<< orphan*/  esas2r_start_vda_request (struct esas2r_adapter*,struct esas2r_request*) ; 
 int /*<<< orphan*/  esas2r_wait_request (struct esas2r_adapter*,struct esas2r_request*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

bool esas2r_init_msgs(struct esas2r_adapter *a)
{
	bool success = true;
	struct esas2r_request *rq = &a->general_req;

	esas2r_rq_init_request(rq, a);
	rq->comp_cb = esas2r_dummy_complete;

	if (a->init_msg == 0)
		a->init_msg = ESAS2R_INIT_MSG_REINIT;

	while (a->init_msg) {
		if (esas2r_format_init_msg(a, rq)) {
			unsigned long flags;
			while (true) {
				spin_lock_irqsave(&a->queue_lock, flags);
				esas2r_start_vda_request(a, rq);
				spin_unlock_irqrestore(&a->queue_lock, flags);
				esas2r_wait_request(a, rq);
				if (rq->req_stat != RS_PENDING)
					break;
			}
		}

		if (rq->req_stat == RS_SUCCESS
		    || ((rq->flags & RF_FAILURE_OK)
			&& rq->req_stat != RS_TIMEOUT))
			continue;

		esas2r_log(ESAS2R_LOG_CRIT, "init message %x failed (%x, %x)",
			   a->init_msg, rq->req_stat, rq->flags);
		a->init_msg = ESAS2R_INIT_MSG_START;
		success = false;
		break;
	}

	esas2r_rq_destroy_request(rq, a);
	return success;
}