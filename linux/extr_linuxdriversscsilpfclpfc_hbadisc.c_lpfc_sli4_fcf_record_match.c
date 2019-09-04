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
typedef  scalar_t__ uint16_t ;
struct lpfc_hba {int dummy; } ;
struct lpfc_fcf_rec {scalar_t__ priority; int /*<<< orphan*/  fabric_name; int /*<<< orphan*/  switch_name; int /*<<< orphan*/  mac_addr; int /*<<< orphan*/  vlan_id; } ;
struct fcf_record {scalar_t__ fip_priority; } ;

/* Variables and functions */
 scalar_t__ LPFC_FCOE_IGNORE_VID ; 
 int /*<<< orphan*/  lpfc_fab_name_match (int /*<<< orphan*/ ,struct fcf_record*) ; 
 int /*<<< orphan*/  lpfc_mac_addr_match (int /*<<< orphan*/ ,struct fcf_record*) ; 
 int /*<<< orphan*/  lpfc_sw_name_match (int /*<<< orphan*/ ,struct fcf_record*) ; 
 int /*<<< orphan*/  lpfc_vlan_id_match (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static bool
lpfc_sli4_fcf_record_match(struct lpfc_hba *phba,
			   struct lpfc_fcf_rec *fcf_rec,
			   struct fcf_record *new_fcf_record,
			   uint16_t new_vlan_id)
{
	if (new_vlan_id != LPFC_FCOE_IGNORE_VID)
		if (!lpfc_vlan_id_match(fcf_rec->vlan_id, new_vlan_id))
			return false;
	if (!lpfc_mac_addr_match(fcf_rec->mac_addr, new_fcf_record))
		return false;
	if (!lpfc_sw_name_match(fcf_rec->switch_name, new_fcf_record))
		return false;
	if (!lpfc_fab_name_match(fcf_rec->fabric_name, new_fcf_record))
		return false;
	if (fcf_rec->priority != new_fcf_record->fip_priority)
		return false;
	return true;
}