#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_9__ ;
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_10__ ;

/* Type definitions */
struct TYPE_26__ {scalar_t__ comp_status; int /*<<< orphan*/  comp; void* req_que_no; int /*<<< orphan*/  cmd_hndl; } ;
struct TYPE_27__ {TYPE_6__ abt; } ;
struct srb_iocb {TYPE_7__ u; int /*<<< orphan*/  timeout; } ;
struct TYPE_21__ {struct srb_iocb iocb_cmd; } ;
struct TYPE_28__ {char* name; int /*<<< orphan*/  (* free ) (TYPE_8__*) ;int /*<<< orphan*/  handle; int /*<<< orphan*/  done; TYPE_4__* qpair; int /*<<< orphan*/  flags; int /*<<< orphan*/  type; TYPE_1__ u; TYPE_10__* fcport; TYPE_9__* vha; } ;
typedef  TYPE_8__ srb_t ;
struct TYPE_22__ {scalar_t__ qpairs_available; } ;
struct TYPE_29__ {TYPE_5__* req; TYPE_2__ flags; } ;
typedef  TYPE_9__ scsi_qla_host_t ;
struct TYPE_20__ {int /*<<< orphan*/  tgt_id; } ;
typedef  TYPE_10__ fc_port_t ;
struct TYPE_25__ {int /*<<< orphan*/  id; } ;
struct TYPE_24__ {TYPE_3__* req; } ;
struct TYPE_23__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 scalar_t__ CS_COMPLETE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int QLA_FUNCTION_FAILED ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  SRB_ABT_CMD ; 
 int /*<<< orphan*/  SRB_WAKEUP_ON_COMP ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,TYPE_9__*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg_async ; 
 int /*<<< orphan*/  qla24xx_abort_iocb_timeout ; 
 int /*<<< orphan*/  qla24xx_abort_sp_done ; 
 int /*<<< orphan*/  qla2x00_get_async_timeout (TYPE_9__*) ; 
 TYPE_8__* qla2x00_get_sp (TYPE_9__*,TYPE_10__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla2x00_init_timer (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int qla2x00_start_sp (TYPE_8__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_8__*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

int
qla24xx_async_abort_cmd(srb_t *cmd_sp, bool wait)
{
	scsi_qla_host_t *vha = cmd_sp->vha;
	fc_port_t *fcport = cmd_sp->fcport;
	struct srb_iocb *abt_iocb;
	srb_t *sp;
	int rval = QLA_FUNCTION_FAILED;

	sp = qla2x00_get_sp(vha, fcport, GFP_KERNEL);
	if (!sp)
		goto done;

	abt_iocb = &sp->u.iocb_cmd;
	sp->type = SRB_ABT_CMD;
	sp->name = "abort";
	if (wait)
		sp->flags = SRB_WAKEUP_ON_COMP;

	abt_iocb->timeout = qla24xx_abort_iocb_timeout;
	init_completion(&abt_iocb->u.abt.comp);
	qla2x00_init_timer(sp, qla2x00_get_async_timeout(vha));

	abt_iocb->u.abt.cmd_hndl = cmd_sp->handle;

	if (vha->flags.qpairs_available && cmd_sp->qpair)
		abt_iocb->u.abt.req_que_no =
		    cpu_to_le16(cmd_sp->qpair->req->id);
	else
		abt_iocb->u.abt.req_que_no = cpu_to_le16(vha->req->id);

	sp->done = qla24xx_abort_sp_done;

	rval = qla2x00_start_sp(sp);
	if (rval != QLA_SUCCESS)
		goto done_free_sp;

	ql_dbg(ql_dbg_async, vha, 0x507c,
	    "Abort command issued - hdl=%x, target_id=%x\n",
	    cmd_sp->handle, fcport->tgt_id);

	if (wait) {
		wait_for_completion(&abt_iocb->u.abt.comp);
		rval = abt_iocb->u.abt.comp_status == CS_COMPLETE ?
			QLA_SUCCESS : QLA_FUNCTION_FAILED;
	} else {
		goto done;
	}

done_free_sp:
	sp->free(sp);
done:
	return rval;
}