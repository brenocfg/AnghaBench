#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;
struct TYPE_19__ {int /*<<< orphan*/ * rsp; int /*<<< orphan*/  rsp_dma; int /*<<< orphan*/  rsp_allocated_size; int /*<<< orphan*/ * req; int /*<<< orphan*/  req_dma; int /*<<< orphan*/  req_allocated_size; } ;
struct TYPE_20__ {TYPE_6__ ctarg; } ;
struct TYPE_21__ {TYPE_7__ u; int /*<<< orphan*/  timer; } ;
struct TYPE_22__ {TYPE_8__ iocb_cmd; } ;
struct srb {scalar_t__ gen2; int rc; int /*<<< orphan*/  (* free ) (struct srb*) ;int /*<<< orphan*/  name; TYPE_9__ u; struct scsi_qla_host* vha; } ;
struct TYPE_16__ {scalar_t__ scan_retry; int /*<<< orphan*/  scan_flags; } ;
struct TYPE_15__ {scalar_t__ nvme_enabled; } ;
struct scsi_qla_host {int /*<<< orphan*/  dpc_flags; TYPE_5__* hw; int /*<<< orphan*/  work_lock; TYPE_3__ scan; TYPE_2__ flags; } ;
struct TYPE_14__ {struct srb* sp; } ;
struct TYPE_13__ {struct srb* sp; int /*<<< orphan*/  fc4_type; } ;
struct TYPE_12__ {TYPE_1__ iosb; TYPE_11__ gpnft; } ;
struct qla_work_evt {TYPE_10__ u; } ;
struct ct_sns_req {int /*<<< orphan*/  command; } ;
struct TYPE_18__ {TYPE_4__* pdev; } ;
struct TYPE_17__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ FC4_TYPE_FCP_SCSI ; 
 int /*<<< orphan*/  FC4_TYPE_NVME ; 
 scalar_t__ GNN_FT_CMD ; 
 scalar_t__ GPN_FT_CMD ; 
 int /*<<< orphan*/  LOCAL_LOOP_UPDATE ; 
 int /*<<< orphan*/  LOOP_RESYNC_NEEDED ; 
 scalar_t__ MAX_SCAN_RETRIES ; 
 int /*<<< orphan*/  QLA_EVT_GNNFT_DONE ; 
 int /*<<< orphan*/  QLA_EVT_GPNFT ; 
 int /*<<< orphan*/  QLA_EVT_GPNFT_DONE ; 
 int /*<<< orphan*/  SF_SCANNING ; 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,struct scsi_qla_host*,int,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  ql_dbg_disc ; 
 struct qla_work_evt* qla2x00_alloc_work (struct scsi_qla_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla2x00_find_free_fcp_nvme_slot (struct scsi_qla_host*,struct srb*) ; 
 int /*<<< orphan*/  qla2x00_post_work (struct scsi_qla_host*,struct qla_work_evt*) ; 
 int /*<<< orphan*/  qla2xxx_wake_dpc (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct srb*) ; 
 int /*<<< orphan*/  stub2 (struct srb*) ; 
 int /*<<< orphan*/  stub3 (struct srb*) ; 

__attribute__((used)) static void qla2x00_async_gpnft_gnnft_sp_done(void *s, int res)
{
	struct srb *sp = s;
	struct scsi_qla_host *vha = sp->vha;
	struct qla_work_evt *e;
	struct ct_sns_req *ct_req =
		(struct ct_sns_req *)sp->u.iocb_cmd.u.ctarg.req;
	u16 cmd = be16_to_cpu(ct_req->command);
	u8 fc4_type = sp->gen2;
	unsigned long flags;

	/* gen2 field is holding the fc4type */
	ql_dbg(ql_dbg_disc, vha, 0xffff,
	    "Async done-%s res %x FC4Type %x\n",
	    sp->name, res, sp->gen2);

	if (res) {
		unsigned long flags;

		sp->free(sp);
		spin_lock_irqsave(&vha->work_lock, flags);
		vha->scan.scan_flags &= ~SF_SCANNING;
		vha->scan.scan_retry++;
		spin_unlock_irqrestore(&vha->work_lock, flags);

		if (vha->scan.scan_retry < MAX_SCAN_RETRIES) {
			set_bit(LOCAL_LOOP_UPDATE, &vha->dpc_flags);
			set_bit(LOOP_RESYNC_NEEDED, &vha->dpc_flags);
			qla2xxx_wake_dpc(vha);
		} else {
			ql_dbg(ql_dbg_disc, sp->vha, 0xffff,
			    "Async done-%s rescan failed on all retries\n",
			    sp->name);
		}
		return;
	}

	if (!res)
		qla2x00_find_free_fcp_nvme_slot(vha, sp);

	if ((fc4_type == FC4_TYPE_FCP_SCSI) && vha->flags.nvme_enabled &&
	    cmd == GNN_FT_CMD) {
		del_timer(&sp->u.iocb_cmd.timer);
		spin_lock_irqsave(&vha->work_lock, flags);
		vha->scan.scan_flags &= ~SF_SCANNING;
		spin_unlock_irqrestore(&vha->work_lock, flags);

		e = qla2x00_alloc_work(vha, QLA_EVT_GPNFT);
		if (!e) {
			/*
			 * please ignore kernel warning. Otherwise,
			 * we have mem leak.
			 */
			if (sp->u.iocb_cmd.u.ctarg.req) {
				dma_free_coherent(&vha->hw->pdev->dev,
				    sp->u.iocb_cmd.u.ctarg.req_allocated_size,
				    sp->u.iocb_cmd.u.ctarg.req,
				    sp->u.iocb_cmd.u.ctarg.req_dma);
				sp->u.iocb_cmd.u.ctarg.req = NULL;
			}
			if (sp->u.iocb_cmd.u.ctarg.rsp) {
				dma_free_coherent(&vha->hw->pdev->dev,
				    sp->u.iocb_cmd.u.ctarg.rsp_allocated_size,
				    sp->u.iocb_cmd.u.ctarg.rsp,
				    sp->u.iocb_cmd.u.ctarg.rsp_dma);
				sp->u.iocb_cmd.u.ctarg.rsp = NULL;
			}

			ql_dbg(ql_dbg_disc, vha, 0xffff,
			    "Async done-%s unable to alloc work element\n",
			    sp->name);
			sp->free(sp);
			set_bit(LOCAL_LOOP_UPDATE, &vha->dpc_flags);
			set_bit(LOOP_RESYNC_NEEDED, &vha->dpc_flags);
			return;
		}
		e->u.gpnft.fc4_type = FC4_TYPE_NVME;
		sp->rc = res;
		e->u.gpnft.sp = sp;

		qla2x00_post_work(vha, e);
		return;
	}

	if (cmd == GPN_FT_CMD)
		e = qla2x00_alloc_work(vha, QLA_EVT_GPNFT_DONE);
	else
		e = qla2x00_alloc_work(vha, QLA_EVT_GNNFT_DONE);
	if (!e) {
		/* please ignore kernel warning. Otherwise, we have mem leak. */
		if (sp->u.iocb_cmd.u.ctarg.req) {
			dma_free_coherent(&vha->hw->pdev->dev,
			    sp->u.iocb_cmd.u.ctarg.req_allocated_size,
			    sp->u.iocb_cmd.u.ctarg.req,
			    sp->u.iocb_cmd.u.ctarg.req_dma);
			sp->u.iocb_cmd.u.ctarg.req = NULL;
		}
		if (sp->u.iocb_cmd.u.ctarg.rsp) {
			dma_free_coherent(&vha->hw->pdev->dev,
			    sp->u.iocb_cmd.u.ctarg.rsp_allocated_size,
			    sp->u.iocb_cmd.u.ctarg.rsp,
			    sp->u.iocb_cmd.u.ctarg.rsp_dma);
			sp->u.iocb_cmd.u.ctarg.rsp = NULL;
		}

		ql_dbg(ql_dbg_disc, vha, 0xffff,
		    "Async done-%s unable to alloc work element\n",
		    sp->name);
		sp->free(sp);
		set_bit(LOCAL_LOOP_UPDATE, &vha->dpc_flags);
		set_bit(LOOP_RESYNC_NEEDED, &vha->dpc_flags);
		return;
	}

	sp->rc = res;
	e->u.iosb.sp = sp;

	qla2x00_post_work(vha, e);
}