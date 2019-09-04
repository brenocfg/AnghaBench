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
struct rtl_phy {int num_total_rfpath; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct phy_dm_struct {int dummy; } ;
typedef  enum odm_rf_radio_path { ____Placeholder_odm_rf_radio_path } odm_rf_radio_path ;
typedef  enum hal_status { ____Placeholder_hal_status } hal_status ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_RF_RADIO ; 
 int HAL_STATUS_SUCCESS ; 
 int odm_config_rf_with_header_file (struct phy_dm_struct*,int /*<<< orphan*/ ,int) ; 
 int odm_config_rf_with_tx_pwr_track_header_file (struct phy_dm_struct*) ; 
 struct phy_dm_struct* rtlpriv_to_phydm (struct rtl_priv*) ; 

__attribute__((used)) static bool rtl_phydm_phy_rf_config(struct rtl_priv *rtlpriv)
{
	struct phy_dm_struct *dm = rtlpriv_to_phydm(rtlpriv);
	struct rtl_phy *rtlphy = &rtlpriv->phy;
	enum hal_status status;
	enum odm_rf_radio_path rfpath;

	for (rfpath = 0; rfpath < rtlphy->num_total_rfpath; rfpath++) {
		status = odm_config_rf_with_header_file(dm, CONFIG_RF_RADIO,
							rfpath);
		if (status != HAL_STATUS_SUCCESS)
			return false;
	}

	status = odm_config_rf_with_tx_pwr_track_header_file(dm);
	if (status != HAL_STATUS_SUCCESS)
		return false;

	return true;
}