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
typedef  int u8 ;
struct phy_status_rpt_8812 {int sigevm; int* rxevm; int* rxevm_cd; } ;
struct dm_per_pkt_info {scalar_t__ data_rate; } ;

/* Variables and functions */
 scalar_t__ ODM_RATE54M ; 
 scalar_t__ ODM_RATE6M ; 
 int ODM_RF_PATH_A ; 
 int ODM_RF_PATH_C ; 
 int odm_evm_db_to_percentage (int) ; 

__attribute__((used)) static inline u8 phydm_get_odm_evm(u8 i, struct dm_per_pkt_info *pktinfo,
				   struct phy_status_rpt_8812 *phy_sta_rpt)
{
	u8 evm = 0;

	if (pktinfo->data_rate >= ODM_RATE6M &&
	    pktinfo->data_rate <= ODM_RATE54M) {
		if (i == ODM_RF_PATH_A) {
			evm = odm_evm_db_to_percentage(
				(phy_sta_rpt->sigevm)); /*dbm*/
			evm += 20;
			if (evm > 100)
				evm = 100;
		}
	} else {
		if (i < ODM_RF_PATH_C) {
			if (phy_sta_rpt->rxevm[i] == -128)
				phy_sta_rpt->rxevm[i] = -25;
			evm = odm_evm_db_to_percentage(
				(phy_sta_rpt->rxevm[i])); /*dbm*/
		} else {
			if (phy_sta_rpt->rxevm_cd[i - 2] == -128)
				phy_sta_rpt->rxevm_cd[i - 2] = -25;
			evm = odm_evm_db_to_percentage(
				(phy_sta_rpt->rxevm_cd[i - 2])); /*dbm*/
		}
	}

	return evm;
}