#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_15__ ;
typedef  struct TYPE_20__   TYPE_14__ ;
typedef  struct TYPE_19__   TYPE_13__ ;
typedef  struct TYPE_18__   TYPE_12__ ;
typedef  struct TYPE_17__   TYPE_11__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
struct TYPE_30__ {int /*<<< orphan*/ * rsp; int /*<<< orphan*/  rsp_dma; int /*<<< orphan*/  rsp_allocated_size; int /*<<< orphan*/ * req; int /*<<< orphan*/  req_dma; int /*<<< orphan*/  req_allocated_size; } ;
struct TYPE_16__ {TYPE_9__ ctarg; } ;
struct TYPE_17__ {TYPE_10__ u; } ;
struct TYPE_18__ {TYPE_11__ iocb_cmd; } ;
struct srb {int gen1; int /*<<< orphan*/  (* free ) (struct srb*) ;TYPE_12__ u; struct scsi_qla_host* vha; int /*<<< orphan*/  elem; int /*<<< orphan*/  name; } ;
struct scsi_qla_host {TYPE_8__* hw; } ;
struct TYPE_19__ {struct srb* sp; } ;
struct TYPE_20__ {TYPE_13__ iosb; } ;
struct qla_work_evt {TYPE_14__ u; } ;
struct TYPE_24__ {int /*<<< orphan*/  al_pa; int /*<<< orphan*/  area; int /*<<< orphan*/  domain; } ;
struct TYPE_21__ {TYPE_3__ b; } ;
struct event_arg {int rc; TYPE_15__ id; int /*<<< orphan*/  event; struct srb* sp; int /*<<< orphan*/  port_name; } ;
struct TYPE_22__ {int /*<<< orphan*/  port_name; } ;
struct TYPE_23__ {TYPE_1__ gpn_id; } ;
struct ct_sns_rsp {TYPE_2__ rsp; } ;
struct TYPE_25__ {int /*<<< orphan*/ * port_id; } ;
struct TYPE_26__ {TYPE_4__ port_id; } ;
struct ct_sns_req {TYPE_5__ req; } ;
typedef  int /*<<< orphan*/  ea ;
struct TYPE_27__ {int /*<<< orphan*/  sess_lock; } ;
struct TYPE_29__ {TYPE_7__* pdev; TYPE_6__ tgt; } ;
struct TYPE_28__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  FCME_GPNID_DONE ; 
 int /*<<< orphan*/  QLA_EVT_UNMAP ; 
 int QLA_FUNCTION_TIMEOUT ; 
 int /*<<< orphan*/  WWN_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct event_arg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,struct scsi_qla_host*,int,char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  ql_dbg_disc ; 
 int /*<<< orphan*/  qla24xx_post_gpnid_work (struct scsi_qla_host*,TYPE_15__*) ; 
 struct qla_work_evt* qla2x00_alloc_work (struct scsi_qla_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla2x00_fcport_event_handler (struct scsi_qla_host*,struct event_arg*) ; 
 int /*<<< orphan*/  qla2x00_post_work (struct scsi_qla_host*,struct qla_work_evt*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct srb*) ; 
 int /*<<< orphan*/  stub2 (struct srb*) ; 
 int /*<<< orphan*/  stub3 (struct srb*) ; 

__attribute__((used)) static void qla2x00_async_gpnid_sp_done(void *s, int res)
{
	struct srb *sp = s;
	struct scsi_qla_host *vha = sp->vha;
	struct ct_sns_req *ct_req =
	    (struct ct_sns_req *)sp->u.iocb_cmd.u.ctarg.req;
	struct ct_sns_rsp *ct_rsp =
	    (struct ct_sns_rsp *)sp->u.iocb_cmd.u.ctarg.rsp;
	struct event_arg ea;
	struct qla_work_evt *e;
	unsigned long flags;

	if (res)
		ql_dbg(ql_dbg_disc, vha, 0x2066,
		    "Async done-%s fail res %x rscn gen %d ID %3phC. %8phC\n",
		    sp->name, res, sp->gen1, ct_req->req.port_id.port_id,
		    ct_rsp->rsp.gpn_id.port_name);
	else
		ql_dbg(ql_dbg_disc, vha, 0x2066,
		    "Async done-%s good rscn gen %d ID %3phC. %8phC\n",
		    sp->name, sp->gen1, ct_req->req.port_id.port_id,
		    ct_rsp->rsp.gpn_id.port_name);

	memset(&ea, 0, sizeof(ea));
	memcpy(ea.port_name, ct_rsp->rsp.gpn_id.port_name, WWN_SIZE);
	ea.sp = sp;
	ea.id.b.domain = ct_req->req.port_id.port_id[0];
	ea.id.b.area = ct_req->req.port_id.port_id[1];
	ea.id.b.al_pa = ct_req->req.port_id.port_id[2];
	ea.rc = res;
	ea.event = FCME_GPNID_DONE;

	spin_lock_irqsave(&vha->hw->tgt.sess_lock, flags);
	list_del(&sp->elem);
	spin_unlock_irqrestore(&vha->hw->tgt.sess_lock, flags);

	if (res) {
		if (res == QLA_FUNCTION_TIMEOUT) {
			qla24xx_post_gpnid_work(sp->vha, &ea.id);
			sp->free(sp);
			return;
		}
	} else if (sp->gen1) {
		/* There was another RSCN for this Nport ID */
		qla24xx_post_gpnid_work(sp->vha, &ea.id);
		sp->free(sp);
		return;
	}

	qla2x00_fcport_event_handler(vha, &ea);

	e = qla2x00_alloc_work(vha, QLA_EVT_UNMAP);
	if (!e) {
		/* please ignore kernel warning. otherwise, we have mem leak. */
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

		sp->free(sp);
		return;
	}

	e->u.iosb.sp = sp;
	qla2x00_post_work(vha, e);
}