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
struct request {int cmd_flags; int /*<<< orphan*/  q; } ;
typedef  scalar_t__ blk_status_t ;
struct TYPE_2__ {int /*<<< orphan*/  retries; } ;

/* Variables and functions */
 scalar_t__ BLK_STS_OK ; 
 int REQ_NVME_MPATH ; 
 int /*<<< orphan*/  blk_mq_end_request (struct request*,scalar_t__) ; 
 int /*<<< orphan*/  blk_mq_requeue_request (struct request*,int) ; 
 scalar_t__ blk_path_error (scalar_t__) ; 
 int /*<<< orphan*/  blk_queue_dying (int /*<<< orphan*/ ) ; 
 scalar_t__ nvme_error_status (struct request*) ; 
 int /*<<< orphan*/  nvme_failover_req (struct request*) ; 
 TYPE_1__* nvme_req (struct request*) ; 
 scalar_t__ nvme_req_needs_retry (struct request*) ; 
 int /*<<< orphan*/  trace_nvme_complete_rq (struct request*) ; 
 scalar_t__ unlikely (int) ; 

void nvme_complete_rq(struct request *req)
{
	blk_status_t status = nvme_error_status(req);

	trace_nvme_complete_rq(req);

	if (unlikely(status != BLK_STS_OK && nvme_req_needs_retry(req))) {
		if ((req->cmd_flags & REQ_NVME_MPATH) &&
		    blk_path_error(status)) {
			nvme_failover_req(req);
			return;
		}

		if (!blk_queue_dying(req->q)) {
			nvme_req(req)->retries++;
			blk_mq_requeue_request(req, true);
			return;
		}
	}
	blk_mq_end_request(req, status);
}