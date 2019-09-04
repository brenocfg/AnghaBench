#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct qla_hw_data {int /*<<< orphan*/  ms_iocb_dma; int /*<<< orphan*/  ms_iocb; TYPE_7__* ct_sns; TYPE_1__* isp_ops; } ;
struct ct_sns_rsp {int dummy; } ;
struct TYPE_14__ {int /*<<< orphan*/  port_name; } ;
struct TYPE_15__ {TYPE_3__ dhba; } ;
struct ct_sns_req {TYPE_4__ req; } ;
struct TYPE_16__ {int /*<<< orphan*/  port_name; struct qla_hw_data* hw; } ;
typedef  TYPE_5__ scsi_qla_host_t ;
typedef  int /*<<< orphan*/  ms_iocb_entry_t ;
struct TYPE_13__ {struct ct_sns_rsp rsp; } ;
struct TYPE_17__ {TYPE_2__ p; } ;
struct TYPE_12__ {int /*<<< orphan*/ * (* prep_ms_fdmi_iocb ) (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DHBA_CMD ; 
 int /*<<< orphan*/  DHBA_REQ_SIZE ; 
 int /*<<< orphan*/  DHBA_RSP_SIZE ; 
 int QLA_FUNCTION_FAILED ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  WWN_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,TYPE_5__*,int,char*,...) ; 
 int /*<<< orphan*/  ql_dbg_disc ; 
 int qla2x00_chk_ms_status (TYPE_5__*,int /*<<< orphan*/ *,struct ct_sns_rsp*,char*) ; 
 int qla2x00_issue_iocb (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct ct_sns_req* qla2x00_prep_ct_fdmi_req (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub1 (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qla2x00_fdmi_dhba(scsi_qla_host_t *vha)
{
	int rval;
	struct qla_hw_data *ha = vha->hw;
	ms_iocb_entry_t *ms_pkt;
	struct ct_sns_req *ct_req;
	struct ct_sns_rsp *ct_rsp;

	/* Issue RPA */
	/* Prepare common MS IOCB */
	ms_pkt = ha->isp_ops->prep_ms_fdmi_iocb(vha, DHBA_REQ_SIZE,
	    DHBA_RSP_SIZE);

	/* Prepare CT request */
	ct_req = qla2x00_prep_ct_fdmi_req(ha->ct_sns, DHBA_CMD, DHBA_RSP_SIZE);
	ct_rsp = &ha->ct_sns->p.rsp;

	/* Prepare FDMI command arguments -- portname. */
	memcpy(ct_req->req.dhba.port_name, vha->port_name, WWN_SIZE);

	ql_dbg(ql_dbg_disc, vha, 0x2036,
	    "DHBA portname = %8phN.\n", ct_req->req.dhba.port_name);

	/* Execute MS IOCB */
	rval = qla2x00_issue_iocb(vha, ha->ms_iocb, ha->ms_iocb_dma,
	    sizeof(ms_iocb_entry_t));
	if (rval != QLA_SUCCESS) {
		/*EMPTY*/
		ql_dbg(ql_dbg_disc, vha, 0x2037,
		    "DHBA issue IOCB failed (%d).\n", rval);
	} else if (qla2x00_chk_ms_status(vha, ms_pkt, ct_rsp, "DHBA") !=
	    QLA_SUCCESS) {
		rval = QLA_FUNCTION_FAILED;
	} else {
		ql_dbg(ql_dbg_disc, vha, 0x2038,
		    "DHBA exiting normally.\n");
	}

	return rval;
}