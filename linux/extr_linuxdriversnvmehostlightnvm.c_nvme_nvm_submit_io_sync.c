#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct request_queue {int dummy; } ;
struct request {int dummy; } ;
struct nvme_nvm_command {int dummy; } ;
struct nvm_rq {int /*<<< orphan*/  error; int /*<<< orphan*/  ppa_status; } ;
struct nvm_dev {struct request_queue* q; } ;
struct TYPE_3__ {int /*<<< orphan*/  u64; } ;
struct TYPE_4__ {int flags; int /*<<< orphan*/  status; TYPE_1__ result; } ;

/* Variables and functions */
 int EINTR ; 
 scalar_t__ IS_ERR (struct request*) ; 
 int NVME_REQ_CANCELLED ; 
 int PTR_ERR (struct request*) ; 
 int /*<<< orphan*/  blk_execute_rq (struct request_queue*,int /*<<< orphan*/ *,struct request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_free_request (struct request*) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct nvme_nvm_command*,int /*<<< orphan*/ ,int) ; 
 struct request* nvme_nvm_alloc_request (struct request_queue*,struct nvm_rq*,struct nvme_nvm_command*) ; 
 TYPE_2__* nvme_req (struct request*) ; 

__attribute__((used)) static int nvme_nvm_submit_io_sync(struct nvm_dev *dev, struct nvm_rq *rqd)
{
	struct request_queue *q = dev->q;
	struct request *rq;
	struct nvme_nvm_command cmd;
	int ret = 0;

	memset(&cmd, 0, sizeof(struct nvme_nvm_command));

	rq = nvme_nvm_alloc_request(q, rqd, &cmd);
	if (IS_ERR(rq))
		return PTR_ERR(rq);

	/* I/Os can fail and the error is signaled through rqd. Callers must
	 * handle the error accordingly.
	 */
	blk_execute_rq(q, NULL, rq, 0);
	if (nvme_req(rq)->flags & NVME_REQ_CANCELLED)
		ret = -EINTR;

	rqd->ppa_status = le64_to_cpu(nvme_req(rq)->result.u64);
	rqd->error = nvme_req(rq)->status;

	blk_mq_free_request(rq);

	return ret;
}