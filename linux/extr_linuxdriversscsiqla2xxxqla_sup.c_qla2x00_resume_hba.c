#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct scsi_qla_host {int /*<<< orphan*/  host; int /*<<< orphan*/  dpc_flags; struct qla_hw_data* hw; } ;
struct qla_hw_data {int /*<<< orphan*/  mbx_cmd_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISP_ABORT_NEEDED ; 
 int /*<<< orphan*/  MBX_UPDATE_FLASH_ACTIVE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qla2x00_wait_for_chip_reset (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  qla2xxx_wake_dpc (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  scsi_unblock_requests (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
qla2x00_resume_hba(struct scsi_qla_host *vha)
{
	struct qla_hw_data *ha = vha->hw;

	/* Resume HBA. */
	clear_bit(MBX_UPDATE_FLASH_ACTIVE, &ha->mbx_cmd_flags);
	set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
	qla2xxx_wake_dpc(vha);
	qla2x00_wait_for_chip_reset(vha);
	scsi_unblock_requests(vha->host);
}