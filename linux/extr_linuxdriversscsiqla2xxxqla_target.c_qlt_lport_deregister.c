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
struct TYPE_3__ {int /*<<< orphan*/ * target_lport_ptr; } ;
struct scsi_qla_host {TYPE_1__ vha_tgt; struct Scsi_Host* host; struct qla_hw_data* hw; } ;
struct TYPE_4__ {int /*<<< orphan*/ * tgt_ops; } ;
struct qla_hw_data {TYPE_2__ tgt; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 

void qlt_lport_deregister(struct scsi_qla_host *vha)
{
	struct qla_hw_data *ha = vha->hw;
	struct Scsi_Host *sh = vha->host;
	/*
	 * Clear the target_lport_ptr qla_target_template pointer in qla_hw_data
	 */
	vha->vha_tgt.target_lport_ptr = NULL;
	ha->tgt.tgt_ops = NULL;
	/*
	 * Release the Scsi_Host reference for the underlying qla2xxx host
	 */
	scsi_host_put(sh);
}