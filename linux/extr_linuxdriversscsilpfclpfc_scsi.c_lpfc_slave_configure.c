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
struct scsi_device {TYPE_1__* host; } ;
struct lpfc_vport {int /*<<< orphan*/  cfg_lun_queue_depth; struct lpfc_hba* phba; } ;
struct TYPE_4__ {int /*<<< orphan*/ * sli3_ring; } ;
struct lpfc_hba {int cfg_poll; TYPE_2__ sli; } ;
struct TYPE_3__ {scalar_t__ hostdata; } ;

/* Variables and functions */
 int DISABLE_FCP_RING_INT ; 
 int ENABLE_FCP_RING_POLLING ; 
 int /*<<< orphan*/  HA_R0RE_REQ ; 
 size_t LPFC_FCP_RING ; 
 int /*<<< orphan*/  lpfc_poll_rearm_timer (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_sli_handle_fast_ring_event (struct lpfc_hba*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_change_queue_depth (struct scsi_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lpfc_slave_configure(struct scsi_device *sdev)
{
	struct lpfc_vport *vport = (struct lpfc_vport *) sdev->host->hostdata;
	struct lpfc_hba   *phba = vport->phba;

	scsi_change_queue_depth(sdev, vport->cfg_lun_queue_depth);

	if (phba->cfg_poll & ENABLE_FCP_RING_POLLING) {
		lpfc_sli_handle_fast_ring_event(phba,
			&phba->sli.sli3_ring[LPFC_FCP_RING], HA_R0RE_REQ);
		if (phba->cfg_poll & DISABLE_FCP_RING_INT)
			lpfc_poll_rearm_timer(phba);
	}

	return 0;
}