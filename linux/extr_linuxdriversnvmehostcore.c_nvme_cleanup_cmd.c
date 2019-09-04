#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ bv_offset; int /*<<< orphan*/  bv_page; } ;
struct request {int rq_flags; TYPE_1__ special_vec; TYPE_2__* rq_disk; } ;
struct nvme_ns {int lba_shift; int /*<<< orphan*/  pi_type; } ;
struct TYPE_6__ {scalar_t__ status; } ;
struct TYPE_5__ {struct nvme_ns* private_data; } ;

/* Variables and functions */
 scalar_t__ REQ_OP_READ ; 
 int RQF_SPECIAL_PAYLOAD ; 
 scalar_t__ blk_integrity_rq (struct request*) ; 
 int blk_rq_bytes (struct request*) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 TYPE_3__* nvme_req (struct request*) ; 
 scalar_t__ page_address (int /*<<< orphan*/ ) ; 
 scalar_t__ req_op (struct request*) ; 
 int /*<<< orphan*/  t10_pi_complete (struct request*,int /*<<< orphan*/ ,int) ; 

void nvme_cleanup_cmd(struct request *req)
{
	if (blk_integrity_rq(req) && req_op(req) == REQ_OP_READ &&
	    nvme_req(req)->status == 0) {
		struct nvme_ns *ns = req->rq_disk->private_data;

		t10_pi_complete(req, ns->pi_type,
				blk_rq_bytes(req) >> ns->lba_shift);
	}
	if (req->rq_flags & RQF_SPECIAL_PAYLOAD) {
		kfree(page_address(req->special_vec.bv_page) +
		      req->special_vec.bv_offset);
	}
}