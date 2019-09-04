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
struct phy_dm_struct {int support_ability; int support_platform; } ;

/* Variables and functions */
#define  ODM_AP 130 
 int ODM_BB_DYNAMIC_TXPWR ; 
#define  ODM_CE 129 
#define  ODM_WIN 128 
 int /*<<< orphan*/  odm_dynamic_tx_power_ap (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  odm_dynamic_tx_power_nic (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  odm_dynamic_tx_power_nic_ce (struct phy_dm_struct*) ; 

void odm_dynamic_tx_power(void *dm_void)
{
	/*  */
	/* For AP/ADSL use struct rtl8192cd_priv* */
	/* For CE/NIC use struct void* */
	/*  */
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;

	if (!(dm->support_ability & ODM_BB_DYNAMIC_TXPWR))
		return;
	/* 2011/09/29 MH In HW integration first stage, we provide 4 different
	 * handle to operate at the same time.
	 * In the stage2/3, we need to prive universal interface and merge all
	 * HW dynamic mechanism.
	 */
	switch (dm->support_platform) {
	case ODM_WIN:
		odm_dynamic_tx_power_nic(dm);
		break;
	case ODM_CE:
		odm_dynamic_tx_power_nic_ce(dm);
		break;
	case ODM_AP:
		odm_dynamic_tx_power_ap(dm);
		break;
	default:
		break;
	}
}