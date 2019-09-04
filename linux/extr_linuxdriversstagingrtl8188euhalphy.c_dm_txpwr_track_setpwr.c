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
struct odm_dm_struct {int BbSwingFlagOfdm; int BbSwingFlagCck; int /*<<< orphan*/ * pChannel; int /*<<< orphan*/  Adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  ODM_COMP_TX_PWR_TRACK ; 
 int /*<<< orphan*/  ODM_DBG_LOUD ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct odm_dm_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  phy_set_tx_power_level (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dm_txpwr_track_setpwr(struct odm_dm_struct *dm_odm)
{
	if (dm_odm->BbSwingFlagOfdm || dm_odm->BbSwingFlagCck) {
		ODM_RT_TRACE(dm_odm, ODM_COMP_TX_PWR_TRACK, ODM_DBG_LOUD,
			     ("dm_txpwr_track_setpwr CH=%d\n", *(dm_odm->pChannel)));
		phy_set_tx_power_level(dm_odm->Adapter, *(dm_odm->pChannel));
		dm_odm->BbSwingFlagOfdm = false;
		dm_odm->BbSwingFlagCck = false;
	}
}