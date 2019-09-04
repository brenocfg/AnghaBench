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
typedef  scalar_t__ u8 ;
typedef  size_t u16 ;
struct ra_table {scalar_t__ highest_client_tx_order; int power_tracking_flag; int* link_tx_rate; size_t highest_client_tx_rate_order; } ;
struct phy_dm_struct {scalar_t__ number_linked_client; struct ra_table dm_ra_table; } ;

/* Variables and functions */
 size_t ODM_ASSOCIATE_ENTRY_NUM ; 
 int /*<<< orphan*/  ODM_COMP_RATE_ADAPTIVE ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*,size_t,scalar_t__) ; 
 scalar_t__ phydm_rate_order_compute (struct phy_dm_struct*,int) ; 

__attribute__((used)) static void phydm_ra_common_info_update(void *dm_void)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	struct ra_table *ra_tab = &dm->dm_ra_table;
	u16 macid;
	u8 rate_order_tmp;
	u8 cnt = 0;

	ra_tab->highest_client_tx_order = 0;
	ra_tab->power_tracking_flag = 1;

	if (dm->number_linked_client != 0) {
		for (macid = 0; macid < ODM_ASSOCIATE_ENTRY_NUM; macid++) {
			rate_order_tmp = phydm_rate_order_compute(
				dm, ((ra_tab->link_tx_rate[macid]) & 0x7f));

			if (rate_order_tmp >=
			    (ra_tab->highest_client_tx_order)) {
				ra_tab->highest_client_tx_order =
					rate_order_tmp;
				ra_tab->highest_client_tx_rate_order = macid;
			}

			cnt++;

			if (cnt == dm->number_linked_client)
				break;
		}
		ODM_RT_TRACE(
			dm, ODM_COMP_RATE_ADAPTIVE,
			"MACID[%d], Highest Tx order Update for power tracking: %d\n",
			(ra_tab->highest_client_tx_rate_order),
			(ra_tab->highest_client_tx_order));
	}
}