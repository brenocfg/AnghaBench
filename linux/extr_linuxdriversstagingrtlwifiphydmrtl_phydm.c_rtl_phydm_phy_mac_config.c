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
typedef  enum hal_status { ____Placeholder_hal_status } hal_status ;

/* Variables and functions */
 int HAL_STATUS_SUCCESS ; 
 int odm_config_mac_with_header_file (struct phy_dm_struct*) ; 
 struct phy_dm_struct* rtlpriv_to_phydm (struct rtl_priv*) ; 

__attribute__((used)) static bool rtl_phydm_phy_mac_config(struct rtl_priv *rtlpriv)
{
	struct phy_dm_struct *dm = rtlpriv_to_phydm(rtlpriv);
	enum hal_status status;

	status = odm_config_mac_with_header_file(dm);
	if (status != HAL_STATUS_SUCCESS)
		return false;

	return true;
}