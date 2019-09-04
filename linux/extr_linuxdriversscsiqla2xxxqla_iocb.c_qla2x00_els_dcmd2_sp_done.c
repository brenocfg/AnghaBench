#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  els_resp_pyld_dma; scalar_t__ els_resp_pyld; int /*<<< orphan*/  rx_size; int /*<<< orphan*/  els_plogi_pyld_dma; scalar_t__ els_plogi_pyld; int /*<<< orphan*/  tx_size; int /*<<< orphan*/  comp; } ;
struct TYPE_18__ {TYPE_5__ els_plogi; } ;
struct srb_iocb {TYPE_6__ u; int /*<<< orphan*/  timer; } ;
struct scsi_qla_host {TYPE_4__* hw; int /*<<< orphan*/  dpc_flags; } ;
struct TYPE_19__ {TYPE_9__* sp; } ;
struct TYPE_20__ {TYPE_7__ iosb; } ;
struct qla_work_evt {TYPE_8__ u; } ;
struct event_arg {int rc; int /*<<< orphan*/  event; TYPE_10__* fcport; } ;
struct TYPE_14__ {struct srb_iocb iocb_cmd; } ;
struct TYPE_21__ {int flags; int /*<<< orphan*/  (* free ) (TYPE_9__*) ;struct scsi_qla_host* vha; TYPE_2__ u; int /*<<< orphan*/  handle; int /*<<< orphan*/  name; TYPE_10__* fcport; } ;
typedef  TYPE_9__ srb_t ;
struct TYPE_13__ {int /*<<< orphan*/  b24; } ;
struct TYPE_12__ {int flags; int /*<<< orphan*/  port_name; TYPE_1__ d_id; } ;
typedef  TYPE_10__ fc_port_t ;
typedef  int /*<<< orphan*/  ea ;
struct TYPE_16__ {TYPE_3__* pdev; } ;
struct TYPE_15__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int FCF_ASYNC_ACTIVE ; 
 int FCF_ASYNC_SENT ; 
 int /*<<< orphan*/  FCME_ELS_PLOGI_DONE ; 
 int /*<<< orphan*/  QLA_EVT_UNMAP ; 
 int /*<<< orphan*/  RELOGIN_NEEDED ; 
 int SRB_WAKEUP_ON_COMP ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct event_arg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,struct scsi_qla_host*,int,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg_disc ; 
 struct qla_work_evt* qla2x00_alloc_work (struct scsi_qla_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla2x00_fcport_event_handler (struct scsi_qla_host*,struct event_arg*) ; 
 int /*<<< orphan*/  qla2x00_post_work (struct scsi_qla_host*,struct qla_work_evt*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_9__*) ; 

__attribute__((used)) static void
qla2x00_els_dcmd2_sp_done(void *ptr, int res)
{
	srb_t *sp = ptr;
	fc_port_t *fcport = sp->fcport;
	struct srb_iocb *lio = &sp->u.iocb_cmd;
	struct scsi_qla_host *vha = sp->vha;
	struct event_arg ea;
	struct qla_work_evt *e;

	ql_dbg(ql_dbg_disc, vha, 0x3072,
	    "%s ELS done rc %d hdl=%x, portid=%06x %8phC\n",
	    sp->name, res, sp->handle, fcport->d_id.b24, fcport->port_name);

	fcport->flags &= ~(FCF_ASYNC_SENT|FCF_ASYNC_ACTIVE);
	del_timer(&sp->u.iocb_cmd.timer);

	if (sp->flags & SRB_WAKEUP_ON_COMP)
		complete(&lio->u.els_plogi.comp);
	else {
		if (res) {
			set_bit(RELOGIN_NEEDED, &vha->dpc_flags);
		} else {
			memset(&ea, 0, sizeof(ea));
			ea.fcport = fcport;
			ea.rc = res;
			ea.event = FCME_ELS_PLOGI_DONE;
			qla2x00_fcport_event_handler(vha, &ea);
		}

		e = qla2x00_alloc_work(vha, QLA_EVT_UNMAP);
		if (!e) {
			struct srb_iocb *elsio = &sp->u.iocb_cmd;

			if (elsio->u.els_plogi.els_plogi_pyld)
				dma_free_coherent(&sp->vha->hw->pdev->dev,
				    elsio->u.els_plogi.tx_size,
				    elsio->u.els_plogi.els_plogi_pyld,
				    elsio->u.els_plogi.els_plogi_pyld_dma);

			if (elsio->u.els_plogi.els_resp_pyld)
				dma_free_coherent(&sp->vha->hw->pdev->dev,
				    elsio->u.els_plogi.rx_size,
				    elsio->u.els_plogi.els_resp_pyld,
				    elsio->u.els_plogi.els_resp_pyld_dma);
			sp->free(sp);
			return;
		}
		e->u.iosb.sp = sp;
		qla2x00_post_work(vha, e);
	}
}