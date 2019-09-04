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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct iwl_phy_db {int /*<<< orphan*/  trans; int /*<<< orphan*/  n_group_txp; int /*<<< orphan*/  n_group_papd; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_INFO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  IWL_ERR (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  IWL_PHY_DB_CALIB_CHG_PAPD ; 
 int /*<<< orphan*/  IWL_PHY_DB_CALIB_CHG_TXP ; 
 int /*<<< orphan*/  IWL_PHY_DB_CALIB_NCH ; 
 int /*<<< orphan*/  IWL_PHY_DB_CFG ; 
 int iwl_phy_db_get_section_data (struct iwl_phy_db*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int iwl_phy_db_send_all_channel_groups (struct iwl_phy_db*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iwl_send_phy_db_cmd (struct iwl_phy_db*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int iwl_send_phy_db_data(struct iwl_phy_db *phy_db)
{
	u8 *data = NULL;
	u16 size = 0;
	int err;

	IWL_DEBUG_INFO(phy_db->trans,
		       "Sending phy db data and configuration to runtime image\n");

	/* Send PHY DB CFG section */
	err = iwl_phy_db_get_section_data(phy_db, IWL_PHY_DB_CFG,
					  &data, &size, 0);
	if (err) {
		IWL_ERR(phy_db->trans, "Cannot get Phy DB cfg section\n");
		return err;
	}

	err = iwl_send_phy_db_cmd(phy_db, IWL_PHY_DB_CFG, size, data);
	if (err) {
		IWL_ERR(phy_db->trans,
			"Cannot send HCMD of  Phy DB cfg section\n");
		return err;
	}

	err = iwl_phy_db_get_section_data(phy_db, IWL_PHY_DB_CALIB_NCH,
					  &data, &size, 0);
	if (err) {
		IWL_ERR(phy_db->trans,
			"Cannot get Phy DB non specific channel section\n");
		return err;
	}

	err = iwl_send_phy_db_cmd(phy_db, IWL_PHY_DB_CALIB_NCH, size, data);
	if (err) {
		IWL_ERR(phy_db->trans,
			"Cannot send HCMD of Phy DB non specific channel section\n");
		return err;
	}

	/* Send all the TXP channel specific data */
	err = iwl_phy_db_send_all_channel_groups(phy_db,
						 IWL_PHY_DB_CALIB_CHG_PAPD,
						 phy_db->n_group_papd);
	if (err) {
		IWL_ERR(phy_db->trans,
			"Cannot send channel specific PAPD groups\n");
		return err;
	}

	/* Send all the TXP channel specific data */
	err = iwl_phy_db_send_all_channel_groups(phy_db,
						 IWL_PHY_DB_CALIB_CHG_TXP,
						 phy_db->n_group_txp);
	if (err) {
		IWL_ERR(phy_db->trans,
			"Cannot send channel specific TX power groups\n");
		return err;
	}

	IWL_DEBUG_INFO(phy_db->trans,
		       "Finished sending phy db non channel data\n");
	return 0;
}