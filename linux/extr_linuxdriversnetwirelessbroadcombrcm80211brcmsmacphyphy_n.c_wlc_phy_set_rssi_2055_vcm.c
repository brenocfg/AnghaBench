#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_2__ {scalar_t__ phy_corenum; } ;
struct brcms_phy {TYPE_1__ pubpi; } ;

/* Variables and functions */
 scalar_t__ NPHY_RSSI_SEL_NB ; 
 scalar_t__ PHY_CORE_0 ; 
 int /*<<< orphan*/  RADIO_2055_CORE1_B0_NBRSSI_VCM ; 
 int /*<<< orphan*/  RADIO_2055_CORE1_RXBB_RSSI_CTRL5 ; 
 int /*<<< orphan*/  RADIO_2055_CORE2_B0_NBRSSI_VCM ; 
 int /*<<< orphan*/  RADIO_2055_CORE2_RXBB_RSSI_CTRL5 ; 
 int /*<<< orphan*/  RADIO_2055_NBRSSI_VCM_I_MASK ; 
 scalar_t__ RADIO_2055_NBRSSI_VCM_I_SHIFT ; 
 int /*<<< orphan*/  RADIO_2055_NBRSSI_VCM_Q_MASK ; 
 scalar_t__ RADIO_2055_NBRSSI_VCM_Q_SHIFT ; 
 int /*<<< orphan*/  RADIO_2055_WBRSSI_VCM_IQ_MASK ; 
 scalar_t__ RADIO_2055_WBRSSI_VCM_IQ_SHIFT ; 
 int /*<<< orphan*/  mod_radio_reg (struct brcms_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
wlc_phy_set_rssi_2055_vcm(struct brcms_phy *pi, u8 rssi_type, u8 *vcm_buf)
{
	u8 core;

	for (core = 0; core < pi->pubpi.phy_corenum; core++) {
		if (rssi_type == NPHY_RSSI_SEL_NB) {
			if (core == PHY_CORE_0) {
				mod_radio_reg(pi,
					      RADIO_2055_CORE1_B0_NBRSSI_VCM,
					      RADIO_2055_NBRSSI_VCM_I_MASK,
					      vcm_buf[2 *
						      core] <<
					      RADIO_2055_NBRSSI_VCM_I_SHIFT);
				mod_radio_reg(pi,
					      RADIO_2055_CORE1_RXBB_RSSI_CTRL5,
					      RADIO_2055_NBRSSI_VCM_Q_MASK,
					      vcm_buf[2 * core +
						      1] <<
					      RADIO_2055_NBRSSI_VCM_Q_SHIFT);
			} else {
				mod_radio_reg(pi,
					      RADIO_2055_CORE2_B0_NBRSSI_VCM,
					      RADIO_2055_NBRSSI_VCM_I_MASK,
					      vcm_buf[2 *
						      core] <<
					      RADIO_2055_NBRSSI_VCM_I_SHIFT);
				mod_radio_reg(pi,
					      RADIO_2055_CORE2_RXBB_RSSI_CTRL5,
					      RADIO_2055_NBRSSI_VCM_Q_MASK,
					      vcm_buf[2 * core +
						      1] <<
					      RADIO_2055_NBRSSI_VCM_Q_SHIFT);
			}
		} else {
			if (core == PHY_CORE_0)
				mod_radio_reg(pi,
					      RADIO_2055_CORE1_RXBB_RSSI_CTRL5,
					      RADIO_2055_WBRSSI_VCM_IQ_MASK,
					      vcm_buf[2 *
						      core] <<
					      RADIO_2055_WBRSSI_VCM_IQ_SHIFT);
			else
				mod_radio_reg(pi,
					      RADIO_2055_CORE2_RXBB_RSSI_CTRL5,
					      RADIO_2055_WBRSSI_VCM_IQ_MASK,
					      vcm_buf[2 *
						      core] <<
					      RADIO_2055_WBRSSI_VCM_IQ_SHIFT);
		}
	}
}