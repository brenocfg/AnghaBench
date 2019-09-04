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
typedef  int uint32_t ;
struct lpfc_vport {int fc_myDID; scalar_t__ cfg_scan_down; struct lpfc_hba* phba; } ;
struct lpfc_hba {scalar_t__ fc_topology; int* alpa_map; } ;

/* Variables and functions */
 int FC_MAXLOOP ; 
 scalar_t__ LPFC_TOPOLOGY_LOOP ; 
 int* lpfcAlpaArray ; 
 int /*<<< orphan*/  lpfc_is_link_up (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_setup_disc_node (struct lpfc_vport*,int) ; 

void
lpfc_disc_list_loopmap(struct lpfc_vport *vport)
{
	struct lpfc_hba  *phba = vport->phba;
	int j;
	uint32_t alpa, index;

	if (!lpfc_is_link_up(phba))
		return;

	if (phba->fc_topology != LPFC_TOPOLOGY_LOOP)
		return;

	/* Check for loop map present or not */
	if (phba->alpa_map[0]) {
		for (j = 1; j <= phba->alpa_map[0]; j++) {
			alpa = phba->alpa_map[j];
			if (((vport->fc_myDID & 0xff) == alpa) || (alpa == 0))
				continue;
			lpfc_setup_disc_node(vport, alpa);
		}
	} else {
		/* No alpamap, so try all alpa's */
		for (j = 0; j < FC_MAXLOOP; j++) {
			/* If cfg_scan_down is set, start from highest
			 * ALPA (0xef) to lowest (0x1).
			 */
			if (vport->cfg_scan_down)
				index = j;
			else
				index = FC_MAXLOOP - j - 1;
			alpa = lpfcAlpaArray[index];
			if ((vport->fc_myDID & 0xff) == alpa)
				continue;
			lpfc_setup_disc_node(vport, alpa);
		}
	}
	return;
}