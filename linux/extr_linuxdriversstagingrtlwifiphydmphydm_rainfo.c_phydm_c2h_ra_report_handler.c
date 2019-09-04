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
struct ra_table {int* link_tx_rate; int highest_client_tx_order; int power_tracking_flag; } ;
struct phy_dm_struct {scalar_t__ is_one_entry_only; struct ra_table dm_ra_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  ODM_COMP_RATE_ADAPTIVE ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  phydm_print_rate (struct phy_dm_struct*,int,int /*<<< orphan*/ ) ; 
 int phydm_rate_order_compute (struct phy_dm_struct*,int) ; 
 int /*<<< orphan*/  phydm_update_pwr_track (struct phy_dm_struct*,int) ; 

void phydm_c2h_ra_report_handler(void *dm_void, u8 *cmd_buf, u8 cmd_len)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	struct ra_table *ra_tab = &dm->dm_ra_table;
	u8 macid = cmd_buf[1];
	u8 rate = cmd_buf[0];
	u8 rate_idx = rate & 0x7f; /*remove bit7 SGI*/
	u8 rate_order;

	if (cmd_len >= 4) {
		if (cmd_buf[3] == 0) {
			ODM_RT_TRACE(dm, ODM_COMP_RATE_ADAPTIVE,
				     "TX Init-rate Update[%d]:", macid);
			/**/
		} else if (cmd_buf[3] == 0xff) {
			ODM_RT_TRACE(dm, ODM_COMP_RATE_ADAPTIVE,
				     "FW Level: Fix rate[%d]:", macid);
			/**/
		} else if (cmd_buf[3] == 1) {
			ODM_RT_TRACE(dm, ODM_COMP_RATE_ADAPTIVE,
				     "Try Success[%d]:", macid);
			/**/
		} else if (cmd_buf[3] == 2) {
			ODM_RT_TRACE(dm, ODM_COMP_RATE_ADAPTIVE,
				     "Try Fail & Try Again[%d]:", macid);
			/**/
		} else if (cmd_buf[3] == 3) {
			ODM_RT_TRACE(dm, ODM_COMP_RATE_ADAPTIVE,
				     "rate Back[%d]:", macid);
			/**/
		} else if (cmd_buf[3] == 4) {
			ODM_RT_TRACE(dm, ODM_COMP_RATE_ADAPTIVE,
				     "start rate by RSSI[%d]:", macid);
			/**/
		} else if (cmd_buf[3] == 5) {
			ODM_RT_TRACE(dm, ODM_COMP_RATE_ADAPTIVE,
				     "Try rate[%d]:", macid);
			/**/
		}
	} else {
		ODM_RT_TRACE(dm, ODM_COMP_RATE_ADAPTIVE, "Tx rate Update[%d]:",
			     macid);
		/**/
	}

	phydm_print_rate(dm, rate, ODM_COMP_RATE_ADAPTIVE);

	ra_tab->link_tx_rate[macid] = rate;

	/*trigger power training*/

	rate_order = phydm_rate_order_compute(dm, rate_idx);

	if ((dm->is_one_entry_only) ||
	    ((rate_order > ra_tab->highest_client_tx_order) &&
	     (ra_tab->power_tracking_flag == 1))) {
		phydm_update_pwr_track(dm, rate_idx);
		ra_tab->power_tracking_flag = 0;
	}

	/*trigger dynamic rate ID*/
}