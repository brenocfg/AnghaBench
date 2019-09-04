#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vport_id ;
typedef  void* u64 ;
struct tcm_qla2xxx_lport {struct scsi_qla_host* qla_vha; TYPE_1__* tpg_1; } ;
struct TYPE_4__ {void* target_lport_ptr; } ;
struct scsi_qla_host {struct Scsi_Host* host; TYPE_2__ vha_tgt; } ;
struct fc_vport_identifiers {int disable; int /*<<< orphan*/  vport_type; int /*<<< orphan*/  roles; void* node_name; void* port_name; } ;
struct fc_vport {scalar_t__ dd_data; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  lport_tpg_enabled; } ;

/* Variables and functions */
 int ENODEV ; 
 int EPERM ; 
 int /*<<< orphan*/  FC_PORTTYPE_NPIV ; 
 int /*<<< orphan*/  FC_PORT_ROLE_FCP_INITIATOR ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 struct fc_vport* fc_vport_create (struct Scsi_Host*,int /*<<< orphan*/ ,struct fc_vport_identifiers*) ; 
 int /*<<< orphan*/  memset (struct fc_vport_identifiers*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ qla_ini_mode_enabled (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  scsi_host_get (struct Scsi_Host*) ; 

__attribute__((used)) static int tcm_qla2xxx_lport_register_npiv_cb(struct scsi_qla_host *base_vha,
					      void *target_lport_ptr,
					      u64 npiv_wwpn, u64 npiv_wwnn)
{
	struct fc_vport *vport;
	struct Scsi_Host *sh = base_vha->host;
	struct scsi_qla_host *npiv_vha;
	struct tcm_qla2xxx_lport *lport =
			(struct tcm_qla2xxx_lport *)target_lport_ptr;
	struct tcm_qla2xxx_lport *base_lport =
			(struct tcm_qla2xxx_lport *)base_vha->vha_tgt.target_lport_ptr;
	struct fc_vport_identifiers vport_id;

	if (qla_ini_mode_enabled(base_vha)) {
		pr_err("qla2xxx base_vha not enabled for target mode\n");
		return -EPERM;
	}

	if (!base_lport || !base_lport->tpg_1 ||
	    !atomic_read(&base_lport->tpg_1->lport_tpg_enabled)) {
		pr_err("qla2xxx base_lport or tpg_1 not available\n");
		return -EPERM;
	}

	memset(&vport_id, 0, sizeof(vport_id));
	vport_id.port_name = npiv_wwpn;
	vport_id.node_name = npiv_wwnn;
	vport_id.roles = FC_PORT_ROLE_FCP_INITIATOR;
	vport_id.vport_type = FC_PORTTYPE_NPIV;
	vport_id.disable = false;

	vport = fc_vport_create(sh, 0, &vport_id);
	if (!vport) {
		pr_err("fc_vport_create failed for qla2xxx_npiv\n");
		return -ENODEV;
	}
	/*
	 * Setup local pointer to NPIV vhba + target_lport_ptr
	 */
	npiv_vha = (struct scsi_qla_host *)vport->dd_data;
	npiv_vha->vha_tgt.target_lport_ptr = target_lport_ptr;
	lport->qla_vha = npiv_vha;
	scsi_host_get(npiv_vha->host);
	return 0;
}