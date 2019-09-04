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
typedef  int u16 ;
struct brcms_phy {scalar_t__* tx_power_offset; } ;
typedef  scalar_t__ s8 ;

/* Variables and functions */
 size_t TXP_FIRST_CCK ; 
 int read_phy_reg (struct brcms_phy*,int) ; 
 scalar_t__ wlc_lcnphy_tssi_based_pwr_ctrl_enabled (struct brcms_phy*) ; 
 scalar_t__ wlc_phy_tpc_isenabled_lcnphy (struct brcms_phy*) ; 

void wlc_lcnphy_get_tssi(struct brcms_phy *pi, s8 *ofdm_pwr, s8 *cck_pwr)
{
	s8 cck_offset;
	u16 status;
	status = (read_phy_reg(pi, 0x4ab));
	if (wlc_lcnphy_tssi_based_pwr_ctrl_enabled(pi) &&
	    (status  & (0x1 << 15))) {
		*ofdm_pwr = (s8) (((read_phy_reg(pi, 0x4ab) & (0x1ff << 0))
				   >> 0) >> 1);

		if (wlc_phy_tpc_isenabled_lcnphy(pi))
			cck_offset = pi->tx_power_offset[TXP_FIRST_CCK];
		else
			cck_offset = 0;

		*cck_pwr = *ofdm_pwr + cck_offset;
	} else {
		*cck_pwr = 0;
		*ofdm_pwr = 0;
	}
}