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
typedef  union nvme_result {int dummy; } nvme_result ;
struct request {int dummy; } ;
struct nvme_request {int status; union nvme_result result; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  blk_mq_complete_request (struct request*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 struct nvme_request* nvme_req (struct request*) ; 
 int /*<<< orphan*/  nvme_should_fail (struct request*) ; 

__attribute__((used)) static inline void nvme_end_request(struct request *req, __le16 status,
		union nvme_result result)
{
	struct nvme_request *rq = nvme_req(req);

	rq->status = le16_to_cpu(status) >> 1;
	rq->result = result;
	/* inject error when permitted by fault injection framework */
	nvme_should_fail(req);
	blk_mq_complete_request(req);
}