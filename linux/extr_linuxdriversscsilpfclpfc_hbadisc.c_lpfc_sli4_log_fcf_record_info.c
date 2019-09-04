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
typedef  int /*<<< orphan*/  uint16_t ;
struct lpfc_hba {int dummy; } ;
struct fcf_record {int /*<<< orphan*/  fip_priority; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_FIP ; 
 int /*<<< orphan*/  bf_get (int /*<<< orphan*/ ,struct fcf_record*) ; 
 int /*<<< orphan*/  lpfc_fcf_record_fab_name_0 ; 
 int /*<<< orphan*/  lpfc_fcf_record_fab_name_1 ; 
 int /*<<< orphan*/  lpfc_fcf_record_fab_name_2 ; 
 int /*<<< orphan*/  lpfc_fcf_record_fab_name_3 ; 
 int /*<<< orphan*/  lpfc_fcf_record_fab_name_4 ; 
 int /*<<< orphan*/  lpfc_fcf_record_fab_name_5 ; 
 int /*<<< orphan*/  lpfc_fcf_record_fab_name_6 ; 
 int /*<<< orphan*/  lpfc_fcf_record_fab_name_7 ; 
 int /*<<< orphan*/  lpfc_fcf_record_fcf_avail ; 
 int /*<<< orphan*/  lpfc_fcf_record_fcf_index ; 
 int /*<<< orphan*/  lpfc_fcf_record_fcf_sol ; 
 int /*<<< orphan*/  lpfc_fcf_record_fcf_valid ; 
 int /*<<< orphan*/  lpfc_fcf_record_mac_0 ; 
 int /*<<< orphan*/  lpfc_fcf_record_mac_1 ; 
 int /*<<< orphan*/  lpfc_fcf_record_mac_2 ; 
 int /*<<< orphan*/  lpfc_fcf_record_mac_3 ; 
 int /*<<< orphan*/  lpfc_fcf_record_mac_4 ; 
 int /*<<< orphan*/  lpfc_fcf_record_mac_5 ; 
 int /*<<< orphan*/  lpfc_fcf_record_mac_addr_prov ; 
 int /*<<< orphan*/  lpfc_fcf_record_switch_name_0 ; 
 int /*<<< orphan*/  lpfc_fcf_record_switch_name_1 ; 
 int /*<<< orphan*/  lpfc_fcf_record_switch_name_2 ; 
 int /*<<< orphan*/  lpfc_fcf_record_switch_name_3 ; 
 int /*<<< orphan*/  lpfc_fcf_record_switch_name_4 ; 
 int /*<<< orphan*/  lpfc_fcf_record_switch_name_5 ; 
 int /*<<< orphan*/  lpfc_fcf_record_switch_name_6 ; 
 int /*<<< orphan*/  lpfc_fcf_record_switch_name_7 ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lpfc_sli4_log_fcf_record_info(struct lpfc_hba *phba,
			      struct fcf_record *fcf_record,
			      uint16_t vlan_id,
			      uint16_t next_fcf_index)
{
	lpfc_printf_log(phba, KERN_INFO, LOG_FIP,
			"2764 READ_FCF_RECORD:\n"
			"\tFCF_Index     : x%x\n"
			"\tFCF_Avail     : x%x\n"
			"\tFCF_Valid     : x%x\n"
			"\tFCF_SOL       : x%x\n"
			"\tFIP_Priority  : x%x\n"
			"\tMAC_Provider  : x%x\n"
			"\tLowest VLANID : x%x\n"
			"\tFCF_MAC Addr  : x%x:%x:%x:%x:%x:%x\n"
			"\tFabric_Name   : x%x:%x:%x:%x:%x:%x:%x:%x\n"
			"\tSwitch_Name   : x%x:%x:%x:%x:%x:%x:%x:%x\n"
			"\tNext_FCF_Index: x%x\n",
			bf_get(lpfc_fcf_record_fcf_index, fcf_record),
			bf_get(lpfc_fcf_record_fcf_avail, fcf_record),
			bf_get(lpfc_fcf_record_fcf_valid, fcf_record),
			bf_get(lpfc_fcf_record_fcf_sol, fcf_record),
			fcf_record->fip_priority,
			bf_get(lpfc_fcf_record_mac_addr_prov, fcf_record),
			vlan_id,
			bf_get(lpfc_fcf_record_mac_0, fcf_record),
			bf_get(lpfc_fcf_record_mac_1, fcf_record),
			bf_get(lpfc_fcf_record_mac_2, fcf_record),
			bf_get(lpfc_fcf_record_mac_3, fcf_record),
			bf_get(lpfc_fcf_record_mac_4, fcf_record),
			bf_get(lpfc_fcf_record_mac_5, fcf_record),
			bf_get(lpfc_fcf_record_fab_name_0, fcf_record),
			bf_get(lpfc_fcf_record_fab_name_1, fcf_record),
			bf_get(lpfc_fcf_record_fab_name_2, fcf_record),
			bf_get(lpfc_fcf_record_fab_name_3, fcf_record),
			bf_get(lpfc_fcf_record_fab_name_4, fcf_record),
			bf_get(lpfc_fcf_record_fab_name_5, fcf_record),
			bf_get(lpfc_fcf_record_fab_name_6, fcf_record),
			bf_get(lpfc_fcf_record_fab_name_7, fcf_record),
			bf_get(lpfc_fcf_record_switch_name_0, fcf_record),
			bf_get(lpfc_fcf_record_switch_name_1, fcf_record),
			bf_get(lpfc_fcf_record_switch_name_2, fcf_record),
			bf_get(lpfc_fcf_record_switch_name_3, fcf_record),
			bf_get(lpfc_fcf_record_switch_name_4, fcf_record),
			bf_get(lpfc_fcf_record_switch_name_5, fcf_record),
			bf_get(lpfc_fcf_record_switch_name_6, fcf_record),
			bf_get(lpfc_fcf_record_switch_name_7, fcf_record),
			next_fcf_index);
}