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
struct nvmet_fc_tgtport {int /*<<< orphan*/  fc_target_port; TYPE_1__* ops; } ;
struct nvmet_fc_fcp_iod {TYPE_2__* fcpreq; } ;
struct TYPE_4__ {scalar_t__ timeout; int /*<<< orphan*/  op; } ;
struct TYPE_3__ {int (* fcp_op ) (int /*<<< orphan*/ *,TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  NVMET_FCOP_RSP ; 
 int /*<<< orphan*/  nvmet_fc_abort_op (struct nvmet_fc_tgtport*,struct nvmet_fc_fcp_iod*) ; 
 int /*<<< orphan*/  nvmet_fc_prep_fcp_rsp (struct nvmet_fc_tgtport*,struct nvmet_fc_fcp_iod*) ; 
 int stub1 (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static void
nvmet_fc_xmt_fcp_rsp(struct nvmet_fc_tgtport *tgtport,
				struct nvmet_fc_fcp_iod *fod)
{
	int ret;

	fod->fcpreq->op = NVMET_FCOP_RSP;
	fod->fcpreq->timeout = 0;

	nvmet_fc_prep_fcp_rsp(tgtport, fod);

	ret = tgtport->ops->fcp_op(&tgtport->fc_target_port, fod->fcpreq);
	if (ret)
		nvmet_fc_abort_op(tgtport, fod);
}