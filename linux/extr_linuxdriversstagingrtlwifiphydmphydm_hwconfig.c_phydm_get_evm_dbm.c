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
typedef  size_t u8 ;
struct phy_status_rpt_8812 {int /*<<< orphan*/ * rxevm_cd; int /*<<< orphan*/ * rxevm; } ;
struct dm_phy_status_info {int dummy; } ;

/* Variables and functions */
 size_t ODM_RF_PATH_C ; 
 size_t odm_evm_dbm_jaguar_series (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u8 phydm_get_evm_dbm(u8 i, u8 EVM,
				   struct phy_status_rpt_8812 *phy_sta_rpt,
				   struct dm_phy_status_info *phy_info)
{
	if (i < ODM_RF_PATH_C)
		return odm_evm_dbm_jaguar_series(phy_sta_rpt->rxevm[i]);
	else
		return odm_evm_dbm_jaguar_series(phy_sta_rpt->rxevm_cd[i - 2]);
	/*RT_DISP(FRX, RX_PHY_SQ, ("RXRATE=%x RXEVM=%x EVM=%s%d\n",*/
	/*pktinfo->data_rate, phy_sta_rpt->rxevm[i], "%", EVM));*/
}