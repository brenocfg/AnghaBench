#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * iop; int /*<<< orphan*/ * data; } ;
struct TYPE_9__ {TYPE_2__ logio; } ;
struct srb_iocb {TYPE_3__ u; } ;
struct scsi_qla_host {int dummy; } ;
struct event_arg {int rc; TYPE_5__* sp; TYPE_4__* fcport; int /*<<< orphan*/ * iop; int /*<<< orphan*/ * data; int /*<<< orphan*/  event; } ;
struct TYPE_7__ {struct srb_iocb iocb_cmd; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* free ) (TYPE_5__*) ;TYPE_4__* fcport; int /*<<< orphan*/  name; TYPE_1__ u; struct scsi_qla_host* vha; } ;
typedef  TYPE_5__ srb_t ;
typedef  int /*<<< orphan*/  ea ;
struct TYPE_10__ {int flags; int /*<<< orphan*/  port_name; } ;

/* Variables and functions */
 int FCF_ASYNC_ACTIVE ; 
 int FCF_ASYNC_SENT ; 
 int /*<<< orphan*/  FCME_ADISC_DONE ; 
 int /*<<< orphan*/  memset (struct event_arg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,struct scsi_qla_host*,int,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg_disc ; 
 int /*<<< orphan*/  qla2x00_fcport_event_handler (struct scsi_qla_host*,struct event_arg*) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*) ; 

__attribute__((used)) static void
qla2x00_async_adisc_sp_done(void *ptr, int res)
{
	srb_t *sp = ptr;
	struct scsi_qla_host *vha = sp->vha;
	struct event_arg ea;
	struct srb_iocb *lio = &sp->u.iocb_cmd;

	ql_dbg(ql_dbg_disc, vha, 0x2066,
	    "Async done-%s res %x %8phC\n",
	    sp->name, res, sp->fcport->port_name);

	sp->fcport->flags &= ~(FCF_ASYNC_SENT | FCF_ASYNC_ACTIVE);

	memset(&ea, 0, sizeof(ea));
	ea.event = FCME_ADISC_DONE;
	ea.rc = res;
	ea.data[0] = lio->u.logio.data[0];
	ea.data[1] = lio->u.logio.data[1];
	ea.iop[0] = lio->u.logio.iop[0];
	ea.iop[1] = lio->u.logio.iop[1];
	ea.fcport = sp->fcport;
	ea.sp = sp;

	qla2x00_fcport_event_handler(vha, &ea);

	sp->free(sp);
}