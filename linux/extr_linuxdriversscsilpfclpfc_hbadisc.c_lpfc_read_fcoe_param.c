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
typedef  int /*<<< orphan*/  uint8_t ;
struct lpfc_hba {int valid_vlan; int vlan_id; int /*<<< orphan*/ * fc_map; } ;
struct lpfc_fip_param_hdr {scalar_t__ parm_version; scalar_t__ length; int parm_flags; } ;
struct lpfc_fcoe_params {int /*<<< orphan*/ * fc_map; int /*<<< orphan*/  vlan_tag; } ;

/* Variables and functions */
 scalar_t__ FCOE_PARAM_LENGTH ; 
 scalar_t__ FIPP_VERSION ; 
 int FIPP_VLAN_VALID ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lpfc_read_fcoe_param(struct lpfc_hba *phba,
			uint8_t *buff)
{
	struct lpfc_fip_param_hdr *fcoe_param_hdr;
	struct lpfc_fcoe_params *fcoe_param;

	fcoe_param_hdr = (struct lpfc_fip_param_hdr *)
		buff;
	fcoe_param = (struct lpfc_fcoe_params *)
		(buff + sizeof(struct lpfc_fip_param_hdr));

	if ((fcoe_param_hdr->parm_version != FIPP_VERSION) ||
		(fcoe_param_hdr->length != FCOE_PARAM_LENGTH))
		return;

	if (fcoe_param_hdr->parm_flags & FIPP_VLAN_VALID) {
		phba->valid_vlan = 1;
		phba->vlan_id = le16_to_cpu(fcoe_param->vlan_tag) &
			0xFFF;
	}

	phba->fc_map[0] = fcoe_param->fc_map[0];
	phba->fc_map[1] = fcoe_param->fc_map[1];
	phba->fc_map[2] = fcoe_param->fc_map[2];
	return;
}