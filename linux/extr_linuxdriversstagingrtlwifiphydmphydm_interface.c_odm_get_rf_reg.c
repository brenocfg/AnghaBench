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
struct rtl_priv {int /*<<< orphan*/  hw; } ;
struct phy_dm_struct {scalar_t__ adapter; } ;
typedef  enum radio_path { ____Placeholder_radio_path } radio_path ;
typedef  enum odm_rf_radio_path { ____Placeholder_odm_rf_radio_path } odm_rf_radio_path ;

/* Variables and functions */
 int /*<<< orphan*/  rtl_get_rfreg (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u32 odm_get_rf_reg(struct phy_dm_struct *dm, enum odm_rf_radio_path e_rf_path,
		   u32 reg_addr, u32 bit_mask)
{
	struct rtl_priv *rtlpriv = (struct rtl_priv *)dm->adapter;

	return rtl_get_rfreg(rtlpriv->hw, (enum radio_path)e_rf_path, reg_addr,
			     bit_mask);
}