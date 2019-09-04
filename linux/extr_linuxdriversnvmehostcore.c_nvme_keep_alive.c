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
struct request {int timeout; int /*<<< orphan*/  q; struct nvme_ctrl* end_io_data; } ;
struct nvme_ctrl {int kato; int /*<<< orphan*/  ka_cmd; int /*<<< orphan*/  admin_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_MQ_REQ_RESERVED ; 
 int HZ ; 
 scalar_t__ IS_ERR (struct request*) ; 
 int /*<<< orphan*/  NVME_QID_ANY ; 
 int PTR_ERR (struct request*) ; 
 int /*<<< orphan*/  blk_execute_rq_nowait (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct request* nvme_alloc_request (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_keep_alive_end_io ; 

__attribute__((used)) static int nvme_keep_alive(struct nvme_ctrl *ctrl)
{
	struct request *rq;

	rq = nvme_alloc_request(ctrl->admin_q, &ctrl->ka_cmd, BLK_MQ_REQ_RESERVED,
			NVME_QID_ANY);
	if (IS_ERR(rq))
		return PTR_ERR(rq);

	rq->timeout = ctrl->kato * HZ;
	rq->end_io_data = ctrl;

	blk_execute_rq_nowait(rq->q, NULL, rq, 0, nvme_keep_alive_end_io);

	return 0;
}