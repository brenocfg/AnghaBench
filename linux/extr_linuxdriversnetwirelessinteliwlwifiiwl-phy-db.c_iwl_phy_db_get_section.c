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
typedef  size_t u16 ;
struct iwl_phy_db_entry {int dummy; } ;
struct iwl_phy_db {size_t n_group_papd; size_t n_group_txp; struct iwl_phy_db_entry* calib_ch_group_txp; struct iwl_phy_db_entry* calib_ch_group_papd; struct iwl_phy_db_entry calib_nch; struct iwl_phy_db_entry cfg; } ;
typedef  enum iwl_phy_db_section_type { ____Placeholder_iwl_phy_db_section_type } iwl_phy_db_section_type ;

/* Variables and functions */
#define  IWL_PHY_DB_CALIB_CHG_PAPD 131 
#define  IWL_PHY_DB_CALIB_CHG_TXP 130 
#define  IWL_PHY_DB_CALIB_NCH 129 
#define  IWL_PHY_DB_CFG 128 
 int IWL_PHY_DB_MAX ; 

__attribute__((used)) static struct iwl_phy_db_entry *
iwl_phy_db_get_section(struct iwl_phy_db *phy_db,
		       enum iwl_phy_db_section_type type,
		       u16 chg_id)
{
	if (!phy_db || type >= IWL_PHY_DB_MAX)
		return NULL;

	switch (type) {
	case IWL_PHY_DB_CFG:
		return &phy_db->cfg;
	case IWL_PHY_DB_CALIB_NCH:
		return &phy_db->calib_nch;
	case IWL_PHY_DB_CALIB_CHG_PAPD:
		if (chg_id >= phy_db->n_group_papd)
			return NULL;
		return &phy_db->calib_ch_group_papd[chg_id];
	case IWL_PHY_DB_CALIB_CHG_TXP:
		if (chg_id >= phy_db->n_group_txp)
			return NULL;
		return &phy_db->calib_ch_group_txp[chg_id];
	default:
		return NULL;
	}
	return NULL;
}