#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {struct nvmefc_fcp_req* desc; } ;
struct TYPE_11__ {TYPE_2__ nvme; } ;
struct srb_iocb {TYPE_3__ u; } ;
struct scsi_qla_host {int /*<<< orphan*/  dpc_flags; } ;
struct qla_qpair {int dummy; } ;
struct qla_nvme_rport {TYPE_5__* fcport; } ;
struct nvmefc_fcp_req {struct nvme_private* private; } ;
struct nvme_private {TYPE_4__* sp; } ;
struct nvme_fc_remote_port {struct qla_nvme_rport* private; } ;
struct nvme_fc_local_port {int dummy; } ;
struct TYPE_9__ {struct srb_iocb iocb_cmd; } ;
struct TYPE_12__ {char* name; int /*<<< orphan*/  nvme_ls_waitq; int /*<<< orphan*/  ref_count; TYPE_1__ u; struct qla_qpair* qpair; int /*<<< orphan*/  done; int /*<<< orphan*/  type; } ;
typedef  TYPE_4__ srb_t ;
struct TYPE_13__ {int nvme_flag; struct scsi_qla_host* vha; } ;
typedef  TYPE_5__ fc_port_t ;

/* Variables and functions */
 int /*<<< orphan*/  ABORT_ISP_ACTIVE ; 
 int EBUSY ; 
 int ENODEV ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int NVME_FLAG_RESETTING ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  SRB_NVME_CMD ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,struct scsi_qla_host*,int,char*,...) ; 
 int /*<<< orphan*/  ql_log_warn ; 
 int qla2x00_start_nvme_mq (TYPE_4__*) ; 
 TYPE_4__* qla2xxx_get_qpair_sp (struct qla_qpair*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla_nvme_sp_done ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qla_nvme_post_cmd(struct nvme_fc_local_port *lport,
    struct nvme_fc_remote_port *rport, void *hw_queue_handle,
    struct nvmefc_fcp_req *fd)
{
	fc_port_t *fcport;
	struct srb_iocb *nvme;
	struct scsi_qla_host *vha;
	int rval = -ENODEV;
	srb_t *sp;
	struct qla_qpair *qpair = hw_queue_handle;
	struct nvme_private *priv;
	struct qla_nvme_rport *qla_rport = rport->private;

	if (!fd || !qpair) {
		ql_log(ql_log_warn, NULL, 0x2134,
		    "NO NVMe request or Queue Handle\n");
		return rval;
	}

	priv = fd->private;
	fcport = qla_rport->fcport;
	if (!fcport) {
		ql_log(ql_log_warn, NULL, 0x210e, "No fcport ptr\n");
		return rval;
	}

	vha = fcport->vha;

	if (test_bit(ABORT_ISP_ACTIVE, &vha->dpc_flags))
		return rval;

	/*
	 * If we know the dev is going away while the transport is still sending
	 * IO's return busy back to stall the IO Q.  This happens when the
	 * link goes away and fw hasn't notified us yet, but IO's are being
	 * returned. If the dev comes back quickly we won't exhaust the IO
	 * retry count at the core.
	 */
	if (fcport->nvme_flag & NVME_FLAG_RESETTING)
		return -EBUSY;

	/* Alloc SRB structure */
	sp = qla2xxx_get_qpair_sp(qpair, fcport, GFP_ATOMIC);
	if (!sp)
		return -EBUSY;

	atomic_set(&sp->ref_count, 1);
	init_waitqueue_head(&sp->nvme_ls_waitq);
	priv->sp = sp;
	sp->type = SRB_NVME_CMD;
	sp->name = "nvme_cmd";
	sp->done = qla_nvme_sp_done;
	sp->qpair = qpair;
	nvme = &sp->u.iocb_cmd;
	nvme->u.nvme.desc = fd;

	rval = qla2x00_start_nvme_mq(sp);
	if (rval != QLA_SUCCESS) {
		ql_log(ql_log_warn, vha, 0x212d,
		    "qla2x00_start_nvme_mq failed = %d\n", rval);
		atomic_dec(&sp->ref_count);
		wake_up(&sp->nvme_ls_waitq);
	}

	return rval;
}