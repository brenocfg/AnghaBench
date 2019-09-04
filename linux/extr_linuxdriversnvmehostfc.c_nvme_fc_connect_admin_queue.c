#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_13__ ;
typedef  struct TYPE_16__   TYPE_12__ ;
typedef  struct TYPE_15__   TYPE_11__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
typedef  int u16 ;
struct nvmefc_ls_req {int rqstlen; int rsplen; int /*<<< orphan*/  timeout; struct fcnvme_ls_cr_assoc_acc* rspaddr; struct fcnvme_ls_cr_assoc_rqst* rqstaddr; void* private; } ;
struct nvmefc_ls_req_op {struct nvme_fc_queue* queue; struct nvmefc_ls_req ls_req; } ;
struct nvme_fc_queue {int /*<<< orphan*/  qnum; int /*<<< orphan*/  flags; void* connection_id; } ;
struct TYPE_24__ {TYPE_6__* opts; } ;
struct nvme_fc_ctrl {int /*<<< orphan*/  dev; void* association_id; int /*<<< orphan*/  rport; TYPE_7__ ctrl; TYPE_2__* lport; } ;
struct fcnvme_lsdesc_rqst {int dummy; } ;
struct fcnvme_lsdesc_cr_assoc_cmd {int dummy; } ;
struct fcnvme_lsdesc_conn_id {int dummy; } ;
struct fcnvme_lsdesc_assoc_id {int dummy; } ;
struct TYPE_22__ {int /*<<< orphan*/  subnqn; int /*<<< orphan*/  hostnqn; int /*<<< orphan*/  hostid; void* cntlid; void* sqsize; void* ersp_ratio; scalar_t__ desc_len; scalar_t__ desc_tag; } ;
struct TYPE_20__ {scalar_t__ ls_cmd; } ;
struct fcnvme_ls_cr_assoc_rqst {TYPE_5__ assoc_cmd; scalar_t__ desc_list_len; TYPE_3__ w0; } ;
struct TYPE_17__ {scalar_t__ desc_tag; scalar_t__ desc_len; int /*<<< orphan*/  connection_id; } ;
struct TYPE_16__ {scalar_t__ desc_tag; scalar_t__ desc_len; int /*<<< orphan*/  association_id; } ;
struct TYPE_26__ {scalar_t__ ls_cmd; } ;
struct TYPE_14__ {scalar_t__ desc_tag; scalar_t__ desc_len; TYPE_9__ w0; } ;
struct TYPE_25__ {scalar_t__ ls_cmd; } ;
struct TYPE_15__ {scalar_t__ desc_list_len; TYPE_10__ rqst; TYPE_8__ w0; } ;
struct fcnvme_ls_cr_assoc_acc {TYPE_13__ connectid; TYPE_12__ associd; TYPE_11__ hdr; } ;
struct TYPE_23__ {int /*<<< orphan*/  subsysnqn; TYPE_4__* host; } ;
struct TYPE_21__ {int /*<<< orphan*/  nqn; int /*<<< orphan*/  id; } ;
struct TYPE_19__ {TYPE_1__* ops; } ;
struct TYPE_18__ {int lsrqst_priv_sz; } ;

/* Variables and functions */
 int EBADF ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FCNVME_ASSOC_HOSTNQN_LEN ; 
 int /*<<< orphan*/  FCNVME_ASSOC_SUBNQN_LEN ; 
 int FCNVME_LSDESC_ASSOC_ID ; 
 int FCNVME_LSDESC_CONN_ID ; 
 int FCNVME_LSDESC_CREATE_ASSOC_CMD ; 
 int FCNVME_LSDESC_RQST ; 
 scalar_t__ FCNVME_LS_ACC ; 
 scalar_t__ FCNVME_LS_CREATE_ASSOCIATION ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NVME_FC_CONNECT_TIMEOUT_SEC ; 
 int /*<<< orphan*/  NVME_FC_Q_CONNECTED ; 
 int /*<<< orphan*/  NVMF_NQN_SIZE ; 
 int VERR_ASSOC_ID ; 
 int VERR_ASSOC_ID_LEN ; 
 int VERR_CONN_ID ; 
 int VERR_CONN_ID_LEN ; 
 int VERR_CR_ASSOC ; 
 int VERR_CR_ASSOC_ACC_LEN ; 
 int VERR_LSACC ; 
 int VERR_LSDESC_RQST ; 
 int VERR_LSDESC_RQST_LEN ; 
 void* be64_to_cpu (int /*<<< orphan*/ ) ; 
 void* cpu_to_be16 (int) ; 
 scalar_t__ cpu_to_be32 (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ fcnvme_lsdesc_len (int) ; 
 int /*<<< orphan*/  kfree (struct nvmefc_ls_req_op*) ; 
 struct nvmefc_ls_req_op* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nvme_fc_send_ls_req (int /*<<< orphan*/ ,struct nvmefc_ls_req_op*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uuid_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int* validation_errors ; 

__attribute__((used)) static int
nvme_fc_connect_admin_queue(struct nvme_fc_ctrl *ctrl,
	struct nvme_fc_queue *queue, u16 qsize, u16 ersp_ratio)
{
	struct nvmefc_ls_req_op *lsop;
	struct nvmefc_ls_req *lsreq;
	struct fcnvme_ls_cr_assoc_rqst *assoc_rqst;
	struct fcnvme_ls_cr_assoc_acc *assoc_acc;
	int ret, fcret = 0;

	lsop = kzalloc((sizeof(*lsop) +
			 ctrl->lport->ops->lsrqst_priv_sz +
			 sizeof(*assoc_rqst) + sizeof(*assoc_acc)), GFP_KERNEL);
	if (!lsop) {
		ret = -ENOMEM;
		goto out_no_memory;
	}
	lsreq = &lsop->ls_req;

	lsreq->private = (void *)&lsop[1];
	assoc_rqst = (struct fcnvme_ls_cr_assoc_rqst *)
			(lsreq->private + ctrl->lport->ops->lsrqst_priv_sz);
	assoc_acc = (struct fcnvme_ls_cr_assoc_acc *)&assoc_rqst[1];

	assoc_rqst->w0.ls_cmd = FCNVME_LS_CREATE_ASSOCIATION;
	assoc_rqst->desc_list_len =
			cpu_to_be32(sizeof(struct fcnvme_lsdesc_cr_assoc_cmd));

	assoc_rqst->assoc_cmd.desc_tag =
			cpu_to_be32(FCNVME_LSDESC_CREATE_ASSOC_CMD);
	assoc_rqst->assoc_cmd.desc_len =
			fcnvme_lsdesc_len(
				sizeof(struct fcnvme_lsdesc_cr_assoc_cmd));

	assoc_rqst->assoc_cmd.ersp_ratio = cpu_to_be16(ersp_ratio);
	assoc_rqst->assoc_cmd.sqsize = cpu_to_be16(qsize - 1);
	/* Linux supports only Dynamic controllers */
	assoc_rqst->assoc_cmd.cntlid = cpu_to_be16(0xffff);
	uuid_copy(&assoc_rqst->assoc_cmd.hostid, &ctrl->ctrl.opts->host->id);
	strncpy(assoc_rqst->assoc_cmd.hostnqn, ctrl->ctrl.opts->host->nqn,
		min(FCNVME_ASSOC_HOSTNQN_LEN, NVMF_NQN_SIZE));
	strncpy(assoc_rqst->assoc_cmd.subnqn, ctrl->ctrl.opts->subsysnqn,
		min(FCNVME_ASSOC_SUBNQN_LEN, NVMF_NQN_SIZE));

	lsop->queue = queue;
	lsreq->rqstaddr = assoc_rqst;
	lsreq->rqstlen = sizeof(*assoc_rqst);
	lsreq->rspaddr = assoc_acc;
	lsreq->rsplen = sizeof(*assoc_acc);
	lsreq->timeout = NVME_FC_CONNECT_TIMEOUT_SEC;

	ret = nvme_fc_send_ls_req(ctrl->rport, lsop);
	if (ret)
		goto out_free_buffer;

	/* process connect LS completion */

	/* validate the ACC response */
	if (assoc_acc->hdr.w0.ls_cmd != FCNVME_LS_ACC)
		fcret = VERR_LSACC;
	else if (assoc_acc->hdr.desc_list_len !=
			fcnvme_lsdesc_len(
				sizeof(struct fcnvme_ls_cr_assoc_acc)))
		fcret = VERR_CR_ASSOC_ACC_LEN;
	else if (assoc_acc->hdr.rqst.desc_tag !=
			cpu_to_be32(FCNVME_LSDESC_RQST))
		fcret = VERR_LSDESC_RQST;
	else if (assoc_acc->hdr.rqst.desc_len !=
			fcnvme_lsdesc_len(sizeof(struct fcnvme_lsdesc_rqst)))
		fcret = VERR_LSDESC_RQST_LEN;
	else if (assoc_acc->hdr.rqst.w0.ls_cmd != FCNVME_LS_CREATE_ASSOCIATION)
		fcret = VERR_CR_ASSOC;
	else if (assoc_acc->associd.desc_tag !=
			cpu_to_be32(FCNVME_LSDESC_ASSOC_ID))
		fcret = VERR_ASSOC_ID;
	else if (assoc_acc->associd.desc_len !=
			fcnvme_lsdesc_len(
				sizeof(struct fcnvme_lsdesc_assoc_id)))
		fcret = VERR_ASSOC_ID_LEN;
	else if (assoc_acc->connectid.desc_tag !=
			cpu_to_be32(FCNVME_LSDESC_CONN_ID))
		fcret = VERR_CONN_ID;
	else if (assoc_acc->connectid.desc_len !=
			fcnvme_lsdesc_len(sizeof(struct fcnvme_lsdesc_conn_id)))
		fcret = VERR_CONN_ID_LEN;

	if (fcret) {
		ret = -EBADF;
		dev_err(ctrl->dev,
			"q %d connect failed: %s\n",
			queue->qnum, validation_errors[fcret]);
	} else {
		ctrl->association_id =
			be64_to_cpu(assoc_acc->associd.association_id);
		queue->connection_id =
			be64_to_cpu(assoc_acc->connectid.connection_id);
		set_bit(NVME_FC_Q_CONNECTED, &queue->flags);
	}

out_free_buffer:
	kfree(lsop);
out_no_memory:
	if (ret)
		dev_err(ctrl->dev,
			"queue %d connect admin queue failed (%d).\n",
			queue->qnum, ret);
	return ret;
}