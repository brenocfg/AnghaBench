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
typedef  int u32 ;
struct odm_dm_struct {scalar_t__ BbSwingIdxOfdm; scalar_t__ BbSwingIdxOfdmBase; scalar_t__ BbSwingIdxCck; scalar_t__ BbSwingIdxCckBase; int /*<<< orphan*/  BbSwingFlagOfdm; } ;

/* Variables and functions */
 int /*<<< orphan*/  ODM_COMP_TX_PWR_TRACK ; 
 int /*<<< orphan*/  ODM_DBG_LOUD ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct odm_dm_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int ODM_TXPWRTRACK_MAX_IDX_88E ; 

void rtl88eu_dm_txpower_track_adjust(struct odm_dm_struct *dm_odm, u8 type,
				     u8 *direction, u32 *out_write_val)
{
	u8 pwr_value = 0;
	/*  Tx power tracking BB swing table. */
	if (type == 0) { /* For OFDM adjust */
		ODM_RT_TRACE(dm_odm, ODM_COMP_TX_PWR_TRACK, ODM_DBG_LOUD,
			     ("BbSwingIdxOfdm = %d BbSwingFlagOfdm=%d\n",
			     dm_odm->BbSwingIdxOfdm, dm_odm->BbSwingFlagOfdm));

		if (dm_odm->BbSwingIdxOfdm <= dm_odm->BbSwingIdxOfdmBase) {
			*direction = 1;
			pwr_value = dm_odm->BbSwingIdxOfdmBase -
				     dm_odm->BbSwingIdxOfdm;
		} else {
			*direction = 2;
			pwr_value = dm_odm->BbSwingIdxOfdm -
				     dm_odm->BbSwingIdxOfdmBase;
		}

	} else if (type == 1) { /* For CCK adjust. */
		ODM_RT_TRACE(dm_odm, ODM_COMP_TX_PWR_TRACK, ODM_DBG_LOUD,
			     ("dm_odm->BbSwingIdxCck = %d dm_odm->BbSwingIdxCckBase = %d\n",
			     dm_odm->BbSwingIdxCck, dm_odm->BbSwingIdxCckBase));

		if (dm_odm->BbSwingIdxCck <= dm_odm->BbSwingIdxCckBase) {
			*direction = 1;
			pwr_value = dm_odm->BbSwingIdxCckBase -
				     dm_odm->BbSwingIdxCck;
		} else {
			*direction = 2;
			pwr_value = dm_odm->BbSwingIdxCck -
				     dm_odm->BbSwingIdxCckBase;
		}
	}

	if (pwr_value >= ODM_TXPWRTRACK_MAX_IDX_88E && *direction == 1)
		pwr_value = ODM_TXPWRTRACK_MAX_IDX_88E;

	*out_write_val = pwr_value | (pwr_value<<8) | (pwr_value<<16) |
			 (pwr_value<<24);
}