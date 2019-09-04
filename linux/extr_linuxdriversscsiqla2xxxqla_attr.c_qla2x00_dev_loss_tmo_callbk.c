#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct fc_rport {scalar_t__ dd_data; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; } ;
struct TYPE_6__ {TYPE_4__* vha; int /*<<< orphan*/ * drport; int /*<<< orphan*/  rport; } ;
typedef  TYPE_2__ fc_port_t ;
struct TYPE_7__ {TYPE_1__* hw; int /*<<< orphan*/  dpc_flags; } ;
struct TYPE_5__ {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABORT_ISP_ACTIVE ; 
 int DID_NO_CONNECT ; 
 int /*<<< orphan*/  FCS_DEVICE_DEAD ; 
 int /*<<< orphan*/  pci_channel_offline (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla2x00_abort_all_cmds (TYPE_4__*,int) ; 
 int /*<<< orphan*/  qla2x00_set_fcport_state (TYPE_2__*,int /*<<< orphan*/ ) ; 
 struct Scsi_Host* rport_to_shost (struct fc_rport*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
qla2x00_dev_loss_tmo_callbk(struct fc_rport *rport)
{
	struct Scsi_Host *host = rport_to_shost(rport);
	fc_port_t *fcport = *(fc_port_t **)rport->dd_data;
	unsigned long flags;

	if (!fcport)
		return;

	/* Now that the rport has been deleted, set the fcport state to
	   FCS_DEVICE_DEAD */
	qla2x00_set_fcport_state(fcport, FCS_DEVICE_DEAD);

	/*
	 * Transport has effectively 'deleted' the rport, clear
	 * all local references.
	 */
	spin_lock_irqsave(host->host_lock, flags);
	fcport->rport = fcport->drport = NULL;
	*((fc_port_t **)rport->dd_data) = NULL;
	spin_unlock_irqrestore(host->host_lock, flags);

	if (test_bit(ABORT_ISP_ACTIVE, &fcport->vha->dpc_flags))
		return;

	if (unlikely(pci_channel_offline(fcport->vha->hw->pdev))) {
		qla2x00_abort_all_cmds(fcport->vha, DID_NO_CONNECT << 16);
		return;
	}
}