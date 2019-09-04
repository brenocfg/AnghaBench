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
struct nvmefc_ls_req {struct fcnvme_ls_rjt* rspaddr; } ;
struct nvmefc_ls_req_op {int ls_error; int /*<<< orphan*/  ls_done; struct nvmefc_ls_req ls_req; } ;
struct nvme_fc_rport {int dummy; } ;
struct TYPE_2__ {scalar_t__ ls_cmd; } ;
struct fcnvme_ls_rjt {TYPE_1__ w0; } ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ FCNVME_LS_RJT ; 
 int /*<<< orphan*/  __nvme_fc_finish_ls_req (struct nvmefc_ls_req_op*) ; 
 int __nvme_fc_send_ls_req (struct nvme_fc_rport*,struct nvmefc_ls_req_op*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_fc_send_ls_req_done ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nvme_fc_send_ls_req(struct nvme_fc_rport *rport, struct nvmefc_ls_req_op *lsop)
{
	struct nvmefc_ls_req *lsreq = &lsop->ls_req;
	struct fcnvme_ls_rjt *rjt = lsreq->rspaddr;
	int ret;

	ret = __nvme_fc_send_ls_req(rport, lsop, nvme_fc_send_ls_req_done);

	if (!ret) {
		/*
		 * No timeout/not interruptible as we need the struct
		 * to exist until the lldd calls us back. Thus mandate
		 * wait until driver calls back. lldd responsible for
		 * the timeout action
		 */
		wait_for_completion(&lsop->ls_done);

		__nvme_fc_finish_ls_req(lsop);

		ret = lsop->ls_error;
	}

	if (ret)
		return ret;

	/* ACC or RJT payload ? */
	if (rjt->w0.ls_cmd == FCNVME_LS_RJT)
		return -ENXIO;

	return 0;
}