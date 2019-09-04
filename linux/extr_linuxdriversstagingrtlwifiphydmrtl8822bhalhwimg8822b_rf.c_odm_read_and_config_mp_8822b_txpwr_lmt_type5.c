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
typedef  int u32 ;
struct phy_dm_struct {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__) ; 
 int /*<<< orphan*/  ODM_COMP_INIT ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ array_mp_8822b_txpwr_lmt_type5 ; 
 int /*<<< orphan*/  odm_config_bb_txpwr_lmt_8822b (struct phy_dm_struct*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void odm_read_and_config_mp_8822b_txpwr_lmt_type5(struct phy_dm_struct *dm)
{
	u32 i = 0;
	u8 **array = (u8 **)array_mp_8822b_txpwr_lmt_type5;

	ODM_RT_TRACE(dm, ODM_COMP_INIT,
		     "===> odm_read_and_config_mp_8822b_txpwr_lmt_type5\n");

	for (i = 0; i < ARRAY_SIZE(array_mp_8822b_txpwr_lmt_type5); i += 7) {
		u8 *regulation = array[i];
		u8 *band = array[i + 1];
		u8 *bandwidth = array[i + 2];
		u8 *rate = array[i + 3];
		u8 *rf_path = array[i + 4];
		u8 *chnl = array[i + 5];
		u8 *val = array[i + 6];

		odm_config_bb_txpwr_lmt_8822b(dm, regulation, band, bandwidth,
					      rate, rf_path, chnl, val);
	}
}