#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_6__ {int /*<<< orphan*/  in_dma; int /*<<< orphan*/  in; int /*<<< orphan*/ * in_mb; } ;
struct TYPE_7__ {TYPE_1__ mbx; } ;
struct TYPE_8__ {TYPE_2__ u; } ;
struct TYPE_9__ {TYPE_3__ iocb_cmd; } ;
struct srb {int /*<<< orphan*/  (* free ) (struct srb*) ;TYPE_4__ u; struct scsi_qla_host* vha; int /*<<< orphan*/  name; TYPE_5__* fcport; } ;
struct scsi_qla_host {struct qla_hw_data* hw; } ;
struct qla_hw_data {int /*<<< orphan*/  s_dma_pool; } ;
struct event_arg {struct srb* sp; TYPE_5__* fcport; int /*<<< orphan*/  event; } ;
struct TYPE_10__ {int flags; int /*<<< orphan*/  port_name; } ;
typedef  TYPE_5__ fc_port_t ;
typedef  int /*<<< orphan*/  ea ;

/* Variables and functions */
 int FCF_ASYNC_ACTIVE ; 
 int FCF_ASYNC_SENT ; 
 int /*<<< orphan*/  FCME_GPDB_DONE ; 
 int QLA_FUNCTION_TIMEOUT ; 
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct event_arg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,struct scsi_qla_host*,int,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg_disc ; 
 int /*<<< orphan*/  qla2x00_fcport_event_handler (struct scsi_qla_host*,struct event_arg*) ; 
 int /*<<< orphan*/  stub1 (struct srb*) ; 

__attribute__((used)) static
void qla24xx_async_gpdb_sp_done(void *s, int res)
{
	struct srb *sp = s;
	struct scsi_qla_host *vha = sp->vha;
	struct qla_hw_data *ha = vha->hw;
	fc_port_t *fcport = sp->fcport;
	u16 *mb = sp->u.iocb_cmd.u.mbx.in_mb;
	struct event_arg ea;

	ql_dbg(ql_dbg_disc, vha, 0x20db,
	    "Async done-%s res %x, WWPN %8phC mb[1]=%x mb[2]=%x \n",
	    sp->name, res, fcport->port_name, mb[1], mb[2]);

	fcport->flags &= ~(FCF_ASYNC_SENT | FCF_ASYNC_ACTIVE);

	if (res == QLA_FUNCTION_TIMEOUT)
		return;

	if (res == QLA_FUNCTION_TIMEOUT) {
		dma_pool_free(sp->vha->hw->s_dma_pool, sp->u.iocb_cmd.u.mbx.in,
			sp->u.iocb_cmd.u.mbx.in_dma);
		return;
	}

	memset(&ea, 0, sizeof(ea));
	ea.event = FCME_GPDB_DONE;
	ea.fcport = fcport;
	ea.sp = sp;

	qla2x00_fcport_event_handler(vha, &ea);

	dma_pool_free(ha->s_dma_pool, sp->u.iocb_cmd.u.mbx.in,
		sp->u.iocb_cmd.u.mbx.in_dma);

	sp->free(sp);
}