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
typedef  int /*<<< orphan*/  u8 ;
struct phy_dm_struct {int /*<<< orphan*/  tx_rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  ODM_COMP_TX_PWR_TRACK ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void phydm_update_pwr_track(void *dm_void, u8 rate)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;

	ODM_RT_TRACE(dm, ODM_COMP_TX_PWR_TRACK, "Pwr Track Get rate=0x%x\n",
		     rate);

	dm->tx_rate = rate;
}