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
struct rtl_priv {int dummy; } ;
struct phy_dm_struct {int dummy; } ;
typedef  enum radio_mask { ____Placeholder_radio_mask } radio_mask ;
typedef  enum odm_rf_path { ____Placeholder_odm_rf_path } odm_rf_path ;

/* Variables and functions */
 scalar_t__ IS_HARDWARE_TYPE_8822B (struct rtl_priv*) ; 
 int config_phydm_trx_mode_8822b (struct phy_dm_struct*,int,int,int) ; 
 struct phy_dm_struct* rtlpriv_to_phydm (struct rtl_priv*) ; 

__attribute__((used)) static bool rtl_phydm_trx_mode(struct rtl_priv *rtlpriv,
			       enum radio_mask tx_path, enum radio_mask rx_path,
			       bool is_tx2_path)
{
	struct phy_dm_struct *dm = rtlpriv_to_phydm(rtlpriv);

	if (IS_HARDWARE_TYPE_8822B(rtlpriv))
		return config_phydm_trx_mode_8822b(dm,
						   (enum odm_rf_path)tx_path,
						   (enum odm_rf_path)rx_path,
						   is_tx2_path);

	return false;
}