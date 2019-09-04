#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u64 ;
struct srb {int /*<<< orphan*/  (* free ) (struct srb*) ;int /*<<< orphan*/  name; TYPE_7__* fcport; struct scsi_qla_host* vha; } ;
struct scsi_qla_host {int dummy; } ;
struct event_arg {int rc; int /*<<< orphan*/  event; struct srb* sp; TYPE_7__* fcport; } ;
struct TYPE_13__ {TYPE_5__* ct_sns; } ;
struct TYPE_14__ {int /*<<< orphan*/  fabric_port_name; int /*<<< orphan*/  port_name; TYPE_6__ ct_desc; } ;
typedef  TYPE_7__ fc_port_t ;
typedef  int /*<<< orphan*/  ea ;
struct TYPE_8__ {int /*<<< orphan*/ * port_name; } ;
struct TYPE_9__ {TYPE_1__ gfpn_id; } ;
struct TYPE_10__ {TYPE_2__ rsp; } ;
struct TYPE_11__ {TYPE_3__ rsp; } ;
struct TYPE_12__ {TYPE_4__ p; } ;

/* Variables and functions */
 int /*<<< orphan*/  FCME_GFPNID_DONE ; 
 int /*<<< orphan*/  WWN_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct event_arg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,struct scsi_qla_host*,int,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg_disc ; 
 int /*<<< orphan*/  qla2x00_fcport_event_handler (struct scsi_qla_host*,struct event_arg*) ; 
 int /*<<< orphan*/  stub1 (struct srb*) ; 
 scalar_t__ wwn_to_u64 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qla2x00_async_gfpnid_sp_done(void *s, int res)
{
	struct srb *sp = s;
	struct scsi_qla_host *vha = sp->vha;
	fc_port_t *fcport = sp->fcport;
	u8 *fpn = fcport->ct_desc.ct_sns->p.rsp.rsp.gfpn_id.port_name;
	struct event_arg ea;
	u64 wwn;

	wwn = wwn_to_u64(fpn);
	if (wwn)
		memcpy(fcport->fabric_port_name, fpn, WWN_SIZE);

	memset(&ea, 0, sizeof(ea));
	ea.fcport = fcport;
	ea.sp = sp;
	ea.rc = res;
	ea.event = FCME_GFPNID_DONE;

	ql_dbg(ql_dbg_disc, vha, 0x204f,
	    "Async done-%s res %x, WWPN %8phC %8phC\n",
	    sp->name, res, fcport->port_name, fcport->fabric_port_name);

	qla2x00_fcport_event_handler(vha, &ea);

	sp->free(sp);
}