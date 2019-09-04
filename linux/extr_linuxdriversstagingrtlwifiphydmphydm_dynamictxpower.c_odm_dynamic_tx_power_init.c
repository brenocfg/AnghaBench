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
struct phy_dm_struct {int /*<<< orphan*/  tx_agc_ofdm_18_6; void* dynamic_tx_high_power_lvl; void* last_dtp_lvl; } ;

/* Variables and functions */
 int /*<<< orphan*/  MASKDWORD ; 
 int /*<<< orphan*/  odm_get_bb_reg (struct phy_dm_struct*,int,int /*<<< orphan*/ ) ; 
 void* tx_high_pwr_level_normal ; 

void odm_dynamic_tx_power_init(void *dm_void)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;

	dm->last_dtp_lvl = tx_high_pwr_level_normal;
	dm->dynamic_tx_high_power_lvl = tx_high_pwr_level_normal;
	dm->tx_agc_ofdm_18_6 =
		odm_get_bb_reg(dm, 0xC24, MASKDWORD); /*TXAGC {18M 12M 9M 6M}*/
}