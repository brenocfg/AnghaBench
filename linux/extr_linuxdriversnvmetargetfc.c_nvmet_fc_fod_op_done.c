#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nvmet_fc_tgtport {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  transfer_len; } ;
struct nvmet_fc_fcp_iod {int abort; int writedataactive; int /*<<< orphan*/  queue; TYPE_1__ req; int /*<<< orphan*/  offset; int /*<<< orphan*/  flock; struct nvmet_fc_tgtport* tgtport; struct nvmefc_tgt_fcp_req* fcpreq; } ;
struct nvmefc_tgt_fcp_req {int op; int /*<<< orphan*/  transferred_length; int /*<<< orphan*/  transfer_length; int /*<<< orphan*/  fcp_error; } ;

/* Variables and functions */
#define  NVMET_FCOP_READDATA 131 
#define  NVMET_FCOP_READDATA_RSP 130 
#define  NVMET_FCOP_RSP 129 
#define  NVMET_FCOP_WRITEDATA 128 
 int /*<<< orphan*/  NVME_SC_INTERNAL ; 
 int /*<<< orphan*/  __nvmet_fc_fod_op_abort (struct nvmet_fc_fcp_iod*,int) ; 
 int /*<<< orphan*/  nvmet_fc_abort_op (struct nvmet_fc_tgtport*,struct nvmet_fc_fcp_iod*) ; 
 int /*<<< orphan*/  nvmet_fc_free_fcp_iod (int /*<<< orphan*/ ,struct nvmet_fc_fcp_iod*) ; 
 int /*<<< orphan*/  nvmet_fc_free_tgt_pgs (struct nvmet_fc_fcp_iod*) ; 
 int /*<<< orphan*/  nvmet_fc_transfer_fcp_data (struct nvmet_fc_tgtport*,struct nvmet_fc_fcp_iod*,int const) ; 
 int /*<<< orphan*/  nvmet_fc_xmt_fcp_rsp (struct nvmet_fc_tgtport*,struct nvmet_fc_fcp_iod*) ; 
 int /*<<< orphan*/  nvmet_req_complete (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvmet_req_execute (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
nvmet_fc_fod_op_done(struct nvmet_fc_fcp_iod *fod)
{
	struct nvmefc_tgt_fcp_req *fcpreq = fod->fcpreq;
	struct nvmet_fc_tgtport *tgtport = fod->tgtport;
	unsigned long flags;
	bool abort;

	spin_lock_irqsave(&fod->flock, flags);
	abort = fod->abort;
	fod->writedataactive = false;
	spin_unlock_irqrestore(&fod->flock, flags);

	switch (fcpreq->op) {

	case NVMET_FCOP_WRITEDATA:
		if (__nvmet_fc_fod_op_abort(fod, abort))
			return;
		if (fcpreq->fcp_error ||
		    fcpreq->transferred_length != fcpreq->transfer_length) {
			spin_lock(&fod->flock);
			fod->abort = true;
			spin_unlock(&fod->flock);

			nvmet_req_complete(&fod->req, NVME_SC_INTERNAL);
			return;
		}

		fod->offset += fcpreq->transferred_length;
		if (fod->offset != fod->req.transfer_len) {
			spin_lock_irqsave(&fod->flock, flags);
			fod->writedataactive = true;
			spin_unlock_irqrestore(&fod->flock, flags);

			/* transfer the next chunk */
			nvmet_fc_transfer_fcp_data(tgtport, fod,
						NVMET_FCOP_WRITEDATA);
			return;
		}

		/* data transfer complete, resume with nvmet layer */
		nvmet_req_execute(&fod->req);
		break;

	case NVMET_FCOP_READDATA:
	case NVMET_FCOP_READDATA_RSP:
		if (__nvmet_fc_fod_op_abort(fod, abort))
			return;
		if (fcpreq->fcp_error ||
		    fcpreq->transferred_length != fcpreq->transfer_length) {
			nvmet_fc_abort_op(tgtport, fod);
			return;
		}

		/* success */

		if (fcpreq->op == NVMET_FCOP_READDATA_RSP) {
			/* data no longer needed */
			nvmet_fc_free_tgt_pgs(fod);
			nvmet_fc_free_fcp_iod(fod->queue, fod);
			return;
		}

		fod->offset += fcpreq->transferred_length;
		if (fod->offset != fod->req.transfer_len) {
			/* transfer the next chunk */
			nvmet_fc_transfer_fcp_data(tgtport, fod,
						NVMET_FCOP_READDATA);
			return;
		}

		/* data transfer complete, send response */

		/* data no longer needed */
		nvmet_fc_free_tgt_pgs(fod);

		nvmet_fc_xmt_fcp_rsp(tgtport, fod);

		break;

	case NVMET_FCOP_RSP:
		if (__nvmet_fc_fod_op_abort(fod, abort))
			return;
		nvmet_fc_free_fcp_iod(fod->queue, fod);
		break;

	default:
		break;
	}
}