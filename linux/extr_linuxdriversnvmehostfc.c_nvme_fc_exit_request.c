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
struct request {int dummy; } ;
struct nvme_fc_fcp_op {int dummy; } ;
struct blk_mq_tag_set {int /*<<< orphan*/  driver_data; } ;

/* Variables and functions */
 void __nvme_fc_exit_request (int /*<<< orphan*/ ,struct nvme_fc_fcp_op*) ; 
 struct nvme_fc_fcp_op* blk_mq_rq_to_pdu (struct request*) ; 

__attribute__((used)) static void
nvme_fc_exit_request(struct blk_mq_tag_set *set, struct request *rq,
		unsigned int hctx_idx)
{
	struct nvme_fc_fcp_op *op = blk_mq_rq_to_pdu(rq);

	return __nvme_fc_exit_request(set->driver_data, op);
}