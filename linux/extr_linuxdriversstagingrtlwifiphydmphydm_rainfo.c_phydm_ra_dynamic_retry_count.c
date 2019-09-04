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
struct phy_dm_struct {int support_ability; scalar_t__ pre_b_noisy; scalar_t__ noisy_decision; } ;

/* Variables and functions */
 int /*<<< orphan*/  MASKDWORD ; 
 int ODM_BB_DYNAMIC_ARFR ; 
 int /*<<< orphan*/  ODM_COMP_RATE_ADAPTIVE ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  odm_set_mac_reg (struct phy_dm_struct*,int,int /*<<< orphan*/ ,int) ; 

void phydm_ra_dynamic_retry_count(void *dm_void)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;

	if (!(dm->support_ability & ODM_BB_DYNAMIC_ARFR))
		return;

	if (dm->pre_b_noisy != dm->noisy_decision) {
		if (dm->noisy_decision) {
			ODM_RT_TRACE(dm, ODM_COMP_RATE_ADAPTIVE,
				     "->Noisy Env. RA fallback value\n");
			odm_set_mac_reg(dm, 0x430, MASKDWORD, 0x0);
			odm_set_mac_reg(dm, 0x434, MASKDWORD, 0x04030201);
		} else {
			ODM_RT_TRACE(dm, ODM_COMP_RATE_ADAPTIVE,
				     "->Clean Env. RA fallback value\n");
			odm_set_mac_reg(dm, 0x430, MASKDWORD, 0x01000000);
			odm_set_mac_reg(dm, 0x434, MASKDWORD, 0x06050402);
		}
		dm->pre_b_noisy = dm->noisy_decision;
	}
}