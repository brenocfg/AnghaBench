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
struct brcms_phy {int dummy; } ;

/* Variables and functions */
 scalar_t__ LCNPHY_TX_PWR_CTRL_HW ; 
 scalar_t__ wlc_lcnphy_get_tx_pwr_ctrl (struct brcms_phy*) ; 
 scalar_t__ wlc_lcnphy_tempsense_based_pwr_ctrl_enabled (struct brcms_phy*) ; 

bool wlc_phy_tpc_isenabled_lcnphy(struct brcms_phy *pi)
{
	if (wlc_lcnphy_tempsense_based_pwr_ctrl_enabled(pi))
		return false;
	else
		return (LCNPHY_TX_PWR_CTRL_HW ==
			wlc_lcnphy_get_tx_pwr_ctrl((pi)));
}