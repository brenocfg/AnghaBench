#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_20__ {int /*<<< orphan*/  flags; } ;
struct TYPE_21__ {TYPE_4__ logio; } ;
struct srb_iocb {TYPE_5__ u; int /*<<< orphan*/  timeout; } ;
struct TYPE_17__ {int /*<<< orphan*/  online; } ;
struct scsi_qla_host {int /*<<< orphan*/  dpc_flags; TYPE_1__ flags; } ;
struct TYPE_18__ {struct srb_iocb iocb_cmd; } ;
struct TYPE_24__ {char* name; int /*<<< orphan*/  (* free ) (TYPE_8__*) ;int /*<<< orphan*/  handle; int /*<<< orphan*/  done; TYPE_2__ u; int /*<<< orphan*/  gen2; int /*<<< orphan*/  gen1; int /*<<< orphan*/  type; } ;
typedef  TYPE_8__ srb_t ;
struct TYPE_22__ {int /*<<< orphan*/  al_pa; int /*<<< orphan*/  area; int /*<<< orphan*/  domain; } ;
struct TYPE_23__ {TYPE_6__ b; } ;
struct TYPE_25__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  login_retry; TYPE_7__ d_id; int /*<<< orphan*/  loop_id; int /*<<< orphan*/  port_name; scalar_t__ fc4f_nvme; TYPE_3__* vha; int /*<<< orphan*/  login_gen; int /*<<< orphan*/  rscn_gen; int /*<<< orphan*/  disc_state; scalar_t__ logout_completed; } ;
typedef  TYPE_9__ fc_port_t ;
struct TYPE_19__ {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSC_LOGIN_PEND ; 
 int /*<<< orphan*/  FCF_ASYNC_ACTIVE ; 
 int /*<<< orphan*/  FCF_ASYNC_SENT ; 
 int /*<<< orphan*/  FCF_LOGIN_NEEDED ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ N2N_TOPO (int /*<<< orphan*/ ) ; 
 int QLA_FUNCTION_FAILED ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  RELOGIN_NEEDED ; 
 int /*<<< orphan*/  SRB_LOGIN_CMD ; 
 int /*<<< orphan*/  SRB_LOGIN_COND_PLOGI ; 
 int /*<<< orphan*/  SRB_LOGIN_PRLI_ONLY ; 
 int /*<<< orphan*/  SRB_LOGIN_SKIP_PRLI ; 
 scalar_t__ fcport_is_bigger (TYPE_9__*) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,struct scsi_qla_host*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg_disc ; 
 int /*<<< orphan*/  qla2x00_async_iocb_timeout ; 
 int /*<<< orphan*/  qla2x00_async_login_sp_done ; 
 scalar_t__ qla2x00_get_async_timeout (struct scsi_qla_host*) ; 
 TYPE_8__* qla2x00_get_sp (struct scsi_qla_host*,TYPE_9__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla2x00_init_timer (TYPE_8__*,scalar_t__) ; 
 int qla2x00_start_sp (TYPE_8__*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_8__*) ; 

int
qla2x00_async_login(struct scsi_qla_host *vha, fc_port_t *fcport,
    uint16_t *data)
{
	srb_t *sp;
	struct srb_iocb *lio;
	int rval = QLA_FUNCTION_FAILED;

	if (!vha->flags.online)
		goto done;

	sp = qla2x00_get_sp(vha, fcport, GFP_KERNEL);
	if (!sp)
		goto done;

	fcport->flags |= FCF_ASYNC_SENT;
	fcport->logout_completed = 0;

	fcport->disc_state = DSC_LOGIN_PEND;
	sp->type = SRB_LOGIN_CMD;
	sp->name = "login";
	sp->gen1 = fcport->rscn_gen;
	sp->gen2 = fcport->login_gen;

	lio = &sp->u.iocb_cmd;
	lio->timeout = qla2x00_async_iocb_timeout;
	qla2x00_init_timer(sp, qla2x00_get_async_timeout(vha) + 2);

	sp->done = qla2x00_async_login_sp_done;
	if (N2N_TOPO(fcport->vha->hw) && fcport_is_bigger(fcport)) {
		lio->u.logio.flags |= SRB_LOGIN_PRLI_ONLY;
	} else {
		lio->u.logio.flags |= SRB_LOGIN_COND_PLOGI;

		if (fcport->fc4f_nvme)
			lio->u.logio.flags |= SRB_LOGIN_SKIP_PRLI;

	}

	rval = qla2x00_start_sp(sp);
	if (rval != QLA_SUCCESS) {
		fcport->flags |= FCF_LOGIN_NEEDED;
		set_bit(RELOGIN_NEEDED, &vha->dpc_flags);
		goto done_free_sp;
	}

	ql_dbg(ql_dbg_disc, vha, 0x2072,
	    "Async-login - %8phC hdl=%x, loopid=%x portid=%02x%02x%02x "
		"retries=%d.\n", fcport->port_name, sp->handle, fcport->loop_id,
	    fcport->d_id.b.domain, fcport->d_id.b.area, fcport->d_id.b.al_pa,
	    fcport->login_retry);
	return rval;

done_free_sp:
	sp->free(sp);
	fcport->flags &= ~FCF_ASYNC_SENT;
done:
	fcport->flags &= ~FCF_ASYNC_ACTIVE;
	return rval;
}