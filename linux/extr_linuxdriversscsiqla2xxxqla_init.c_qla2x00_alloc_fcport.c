#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct ct_sns_pkt {int dummy; } ;
struct TYPE_15__ {TYPE_2__* hw; } ;
typedef  TYPE_4__ scsi_qla_host_t ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_14__ {int /*<<< orphan*/  ct_sns; int /*<<< orphan*/  ct_sns_dma; } ;
struct TYPE_16__ {int logout_on_delete; int /*<<< orphan*/  list; int /*<<< orphan*/  gnl_entry; int /*<<< orphan*/  del_work; TYPE_3__ ct_desc; int /*<<< orphan*/  login_retry; int /*<<< orphan*/  deleted; int /*<<< orphan*/  fw_login_state; int /*<<< orphan*/  disc_state; int /*<<< orphan*/  fp_speed; int /*<<< orphan*/  supported_classes; int /*<<< orphan*/  loop_id; int /*<<< orphan*/  port_type; TYPE_4__* vha; } ;
typedef  TYPE_5__ fc_port_t ;
struct TYPE_13__ {int /*<<< orphan*/  login_retry_count; TYPE_1__* pdev; } ;
struct TYPE_12__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSC_DELETED ; 
 int /*<<< orphan*/  DSC_LS_PORT_UNAVAIL ; 
 int /*<<< orphan*/  FCS_UNCONFIGURED ; 
 int /*<<< orphan*/  FCT_UNKNOWN ; 
 int /*<<< orphan*/  FC_COS_UNSPECIFIED ; 
 int /*<<< orphan*/  FC_NO_LOOP_ID ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PORT_SPEED_UNKNOWN ; 
 int /*<<< orphan*/  QLA_SESS_DELETED ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_5__*) ; 
 TYPE_5__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,TYPE_4__*,int,char*) ; 
 int /*<<< orphan*/  ql_log_warn ; 
 int /*<<< orphan*/  qla24xx_delete_sess_fn ; 
 int /*<<< orphan*/  qla2x00_set_fcport_state (TYPE_5__*,int /*<<< orphan*/ ) ; 

fc_port_t *
qla2x00_alloc_fcport(scsi_qla_host_t *vha, gfp_t flags)
{
	fc_port_t *fcport;

	fcport = kzalloc(sizeof(fc_port_t), flags);
	if (!fcport)
		return NULL;

	/* Setup fcport template structure. */
	fcport->vha = vha;
	fcport->port_type = FCT_UNKNOWN;
	fcport->loop_id = FC_NO_LOOP_ID;
	qla2x00_set_fcport_state(fcport, FCS_UNCONFIGURED);
	fcport->supported_classes = FC_COS_UNSPECIFIED;
	fcport->fp_speed = PORT_SPEED_UNKNOWN;

	fcport->ct_desc.ct_sns = dma_alloc_coherent(&vha->hw->pdev->dev,
		sizeof(struct ct_sns_pkt), &fcport->ct_desc.ct_sns_dma,
		flags);
	fcport->disc_state = DSC_DELETED;
	fcport->fw_login_state = DSC_LS_PORT_UNAVAIL;
	fcport->deleted = QLA_SESS_DELETED;
	fcport->login_retry = vha->hw->login_retry_count;
	fcport->logout_on_delete = 1;

	if (!fcport->ct_desc.ct_sns) {
		ql_log(ql_log_warn, vha, 0xd049,
		    "Failed to allocate ct_sns request.\n");
		kfree(fcport);
		fcport = NULL;
	}
	INIT_WORK(&fcport->del_work, qla24xx_delete_sess_fn);
	INIT_LIST_HEAD(&fcport->gnl_entry);
	INIT_LIST_HEAD(&fcport->list);

	return fcport;
}