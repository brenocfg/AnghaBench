#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ mbox_busy; } ;
struct qla_hw_data {TYPE_1__ flags; scalar_t__ dpc_active; int /*<<< orphan*/  pdev; } ;
struct TYPE_7__ {int /*<<< orphan*/  dpc_flags; struct qla_hw_data* hw; } ;
typedef  TYPE_2__ scsi_qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  FX00_RESET_RECOVERY ; 
 int /*<<< orphan*/  FX00_TARGET_SCAN ; 
 int /*<<< orphan*/  UNLOADING ; 
 int /*<<< orphan*/  msleep (int) ; 
 TYPE_2__* pci_get_drvdata (int /*<<< orphan*/ ) ; 
 scalar_t__ qla2x00_reset_active (TYPE_2__*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
qla2x00_wait_for_hba_ready(scsi_qla_host_t *vha)
{
	struct qla_hw_data *ha = vha->hw;
	scsi_qla_host_t *base_vha = pci_get_drvdata(ha->pdev);

	while ((qla2x00_reset_active(vha) || ha->dpc_active ||
		ha->flags.mbox_busy) ||
	       test_bit(FX00_RESET_RECOVERY, &vha->dpc_flags) ||
	       test_bit(FX00_TARGET_SCAN, &vha->dpc_flags)) {
		if (test_bit(UNLOADING, &base_vha->dpc_flags))
			break;
		msleep(1000);
	}
}