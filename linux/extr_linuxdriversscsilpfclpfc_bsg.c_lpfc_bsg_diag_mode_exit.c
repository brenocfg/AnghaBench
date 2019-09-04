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
struct lpfc_vport {int dummy; } ;
struct lpfc_hba {int max_vpi; struct lpfc_vport* pport; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 struct lpfc_vport** lpfc_create_vport_work_array (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_destroy_vport_work_array (struct lpfc_hba*,struct lpfc_vport**) ; 
 struct Scsi_Host* lpfc_shost_from_vport (struct lpfc_vport*) ; 
 int /*<<< orphan*/  scsi_unblock_requests (struct Scsi_Host*) ; 

__attribute__((used)) static void
lpfc_bsg_diag_mode_exit(struct lpfc_hba *phba)
{
	struct Scsi_Host *shost;
	struct lpfc_vport **vports;
	int i;

	vports = lpfc_create_vport_work_array(phba);
	if (vports) {
		for (i = 0; i <= phba->max_vpi && vports[i] != NULL; i++) {
			shost = lpfc_shost_from_vport(vports[i]);
			scsi_unblock_requests(shost);
		}
		lpfc_destroy_vport_work_array(phba, vports);
	} else {
		shost = lpfc_shost_from_vport(phba->pport);
		scsi_unblock_requests(shost);
	}
	return;
}