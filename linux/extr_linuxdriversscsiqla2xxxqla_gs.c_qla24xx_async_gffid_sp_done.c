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
struct srb {int /*<<< orphan*/  (* free ) (struct srb*) ;TYPE_7__* fcport; int /*<<< orphan*/  name; struct scsi_qla_host* vha; } ;
struct scsi_qla_host {int dummy; } ;
struct event_arg {int rc; int /*<<< orphan*/  event; TYPE_7__* fcport; struct srb* sp; } ;
struct TYPE_12__ {int* fc4_features; } ;
struct TYPE_13__ {TYPE_5__ gff_id; } ;
struct ct_sns_rsp {TYPE_6__ rsp; } ;
struct TYPE_11__ {TYPE_3__* ct_sns; } ;
struct TYPE_8__ {int /*<<< orphan*/  b24; } ;
struct TYPE_14__ {int fc4_type; int fc4f_nvme; TYPE_4__ ct_desc; int /*<<< orphan*/  flags; int /*<<< orphan*/  port_name; TYPE_1__ d_id; } ;
typedef  TYPE_7__ fc_port_t ;
typedef  int /*<<< orphan*/  ea ;
struct TYPE_9__ {struct ct_sns_rsp rsp; } ;
struct TYPE_10__ {TYPE_2__ p; } ;

/* Variables and functions */
 int /*<<< orphan*/  FCF_ASYNC_SENT ; 
 int /*<<< orphan*/  FCME_GFFID_DONE ; 
 size_t GFF_FCP_SCSI_OFFSET ; 
 size_t GFF_NVME_OFFSET ; 
 int /*<<< orphan*/  memset (struct event_arg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,struct scsi_qla_host*,int,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg_disc ; 
 int /*<<< orphan*/  qla2x00_fcport_event_handler (struct scsi_qla_host*,struct event_arg*) ; 
 int /*<<< orphan*/  stub1 (struct srb*) ; 

void qla24xx_async_gffid_sp_done(void *s, int res)
{
       struct srb *sp = s;
       struct scsi_qla_host *vha = sp->vha;
       fc_port_t *fcport = sp->fcport;
       struct ct_sns_rsp *ct_rsp;
       struct event_arg ea;

       ql_dbg(ql_dbg_disc, vha, 0x2133,
	   "Async done-%s res %x ID %x. %8phC\n",
	   sp->name, res, fcport->d_id.b24, fcport->port_name);

       fcport->flags &= ~FCF_ASYNC_SENT;
       ct_rsp = &fcport->ct_desc.ct_sns->p.rsp;
       /*
	* FC-GS-7, 5.2.3.12 FC-4 Features - format
	* The format of the FC-4 Features object, as defined by the FC-4,
	* Shall be an array of 4-bit values, one for each type code value
	*/
       if (!res) {
	       if (ct_rsp->rsp.gff_id.fc4_features[GFF_FCP_SCSI_OFFSET] & 0xf) {
		       /* w1 b00:03 */
		       fcport->fc4_type =
			   ct_rsp->rsp.gff_id.fc4_features[GFF_FCP_SCSI_OFFSET];
		       fcport->fc4_type &= 0xf;
	       }

	       if (ct_rsp->rsp.gff_id.fc4_features[GFF_NVME_OFFSET] & 0xf) {
		       /* w5 [00:03]/28h */
		       fcport->fc4f_nvme =
			   ct_rsp->rsp.gff_id.fc4_features[GFF_NVME_OFFSET];
		       fcport->fc4f_nvme &= 0xf;
	       }
       }

       memset(&ea, 0, sizeof(ea));
       ea.sp = sp;
       ea.fcport = sp->fcport;
       ea.rc = res;
       ea.event = FCME_GFFID_DONE;

       qla2x00_fcport_event_handler(vha, &ea);
       sp->free(sp);
}