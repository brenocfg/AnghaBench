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
struct request_queue {int dummy; } ;
struct request {struct nvm_rq* end_io_data; } ;
struct nvme_nvm_command {int dummy; } ;
struct nvm_rq {int dummy; } ;
struct nvm_dev {struct request_queue* q; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct request*) ; 
 int PTR_ERR (struct request*) ; 
 int /*<<< orphan*/  blk_execute_rq_nowait (struct request_queue*,int /*<<< orphan*/ *,struct request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nvme_nvm_command*) ; 
 struct nvme_nvm_command* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct request* nvme_nvm_alloc_request (struct request_queue*,struct nvm_rq*,struct nvme_nvm_command*) ; 
 int /*<<< orphan*/  nvme_nvm_end_io ; 

__attribute__((used)) static int nvme_nvm_submit_io(struct nvm_dev *dev, struct nvm_rq *rqd)
{
	struct request_queue *q = dev->q;
	struct nvme_nvm_command *cmd;
	struct request *rq;

	cmd = kzalloc(sizeof(struct nvme_nvm_command), GFP_KERNEL);
	if (!cmd)
		return -ENOMEM;

	rq = nvme_nvm_alloc_request(q, rqd, cmd);
	if (IS_ERR(rq)) {
		kfree(cmd);
		return PTR_ERR(rq);
	}

	rq->end_io_data = rqd;

	blk_execute_rq_nowait(q, NULL, rq, 0, nvme_nvm_end_io);

	return 0;
}