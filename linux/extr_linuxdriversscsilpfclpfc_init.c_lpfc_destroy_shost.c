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
struct lpfc_hba {struct lpfc_vport* pport; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_port (struct lpfc_vport*) ; 

__attribute__((used)) static void
lpfc_destroy_shost(struct lpfc_hba *phba)
{
	struct lpfc_vport *vport = phba->pport;

	/* Destroy physical port that associated with the SCSI host */
	destroy_port(vport);

	return;
}