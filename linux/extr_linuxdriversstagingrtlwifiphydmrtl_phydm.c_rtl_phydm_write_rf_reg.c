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
typedef  int /*<<< orphan*/  u32 ;
struct rtl_priv {int dummy; } ;
struct phy_dm_struct {int dummy; } ;
typedef  enum radio_path { ____Placeholder_radio_path } radio_path ;
typedef  enum odm_rf_radio_path { ____Placeholder_odm_rf_radio_path } odm_rf_radio_path ;

/* Variables and functions */
 scalar_t__ IS_HARDWARE_TYPE_8822B (struct rtl_priv*) ; 
 int config_phydm_write_rf_reg_8822b (struct phy_dm_struct*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct phy_dm_struct* rtlpriv_to_phydm (struct rtl_priv*) ; 

__attribute__((used)) static bool rtl_phydm_write_rf_reg(struct rtl_priv *rtlpriv,
				   enum radio_path rfpath, u32 addr, u32 mask,
				   u32 data)
{
	struct phy_dm_struct *dm = rtlpriv_to_phydm(rtlpriv);
	enum odm_rf_radio_path odm_rfpath = (enum odm_rf_radio_path)rfpath;

	if (IS_HARDWARE_TYPE_8822B(rtlpriv))
		return config_phydm_write_rf_reg_8822b(dm, odm_rfpath, addr,
						       mask, data);

	return false;
}