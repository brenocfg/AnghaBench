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
struct request_queue {int /*<<< orphan*/  queuedata; } ;
struct request {int dummy; } ;
struct fc_rport {scalar_t__ port_state; int flags; } ;

/* Variables and functions */
 int BLKPREP_DEFER ; 
 int BLKPREP_KILL ; 
 int BLKPREP_OK ; 
 scalar_t__ FC_PORTSTATE_BLOCKED ; 
 scalar_t__ FC_PORTSTATE_ONLINE ; 
 int FC_RPORT_FAST_FAIL_TIMEDOUT ; 
 struct fc_rport* dev_to_rport (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fc_bsg_rport_prep(struct request_queue *q, struct request *req)
{
	struct fc_rport *rport = dev_to_rport(q->queuedata);

	if (rport->port_state == FC_PORTSTATE_BLOCKED &&
	    !(rport->flags & FC_RPORT_FAST_FAIL_TIMEDOUT))
		return BLKPREP_DEFER;

	if (rport->port_state != FC_PORTSTATE_ONLINE)
		return BLKPREP_KILL;

	return BLKPREP_OK;
}