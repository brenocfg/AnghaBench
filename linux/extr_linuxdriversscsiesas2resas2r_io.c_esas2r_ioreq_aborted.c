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
typedef  int /*<<< orphan*/  u8 ;
struct esas2r_request {scalar_t__ timeout; int /*<<< orphan*/  req_stat; int /*<<< orphan*/  req_list; } ;
struct esas2r_adapter {int dummy; } ;

/* Variables and functions */
 scalar_t__ RQ_MAX_TIMEOUT ; 
 int /*<<< orphan*/  RS_BUSY ; 
 int /*<<< orphan*/  esas2r_trace (char*,struct esas2r_request*) ; 
 int /*<<< orphan*/  esas2r_trace_enter () ; 
 int /*<<< orphan*/  esas2r_trace_exit () ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 

bool esas2r_ioreq_aborted(struct esas2r_adapter *a, struct esas2r_request *rq,
			  u8 status)
{
	esas2r_trace_enter();
	esas2r_trace("rq:%p", rq);
	list_del_init(&rq->req_list);
	if (rq->timeout > RQ_MAX_TIMEOUT) {
		/*
		 * The request timed out, but we could not abort it because a
		 * chip reset occurred.  Return busy status.
		 */
		rq->req_stat = RS_BUSY;
		esas2r_trace_exit();
		return true;
	}

	rq->req_stat = status;
	esas2r_trace_exit();
	return true;
}