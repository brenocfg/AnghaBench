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
typedef  void* u32 ;
struct phy_dm_struct {scalar_t__ last_tx_ok_cnt; scalar_t__* num_tx_bytes_unicast; scalar_t__ last_rx_ok_cnt; scalar_t__* num_rx_bytes_unicast; int cur_tx_ok_cnt; int cur_rx_ok_cnt; int tx_tp; int rx_tp; int total_tp; int /*<<< orphan*/  traffic_load; int /*<<< orphan*/  pre_traffic_load; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRAFFIC_HIGH ; 
 int /*<<< orphan*/  TRAFFIC_LOW ; 
 int /*<<< orphan*/  TRAFFIC_MID ; 
 int /*<<< orphan*/  TRAFFIC_ULTRA_LOW ; 

__attribute__((used)) static void phydm_traffic_load_decision(void *dm_void)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;

	/*---TP & Traffic-load calculation---*/

	if (dm->last_tx_ok_cnt > *dm->num_tx_bytes_unicast)
		dm->last_tx_ok_cnt = *dm->num_tx_bytes_unicast;

	if (dm->last_rx_ok_cnt > *dm->num_rx_bytes_unicast)
		dm->last_rx_ok_cnt = *dm->num_rx_bytes_unicast;

	dm->cur_tx_ok_cnt = *dm->num_tx_bytes_unicast - dm->last_tx_ok_cnt;
	dm->cur_rx_ok_cnt = *dm->num_rx_bytes_unicast - dm->last_rx_ok_cnt;
	dm->last_tx_ok_cnt = *dm->num_tx_bytes_unicast;
	dm->last_rx_ok_cnt = *dm->num_rx_bytes_unicast;

	dm->tx_tp = ((dm->tx_tp) >> 1) +
		    (u32)(((dm->cur_tx_ok_cnt) >> 18) >>
			  1); /* <<3(8bit), >>20(10^6,M), >>1(2sec)*/
	dm->rx_tp = ((dm->rx_tp) >> 1) +
		    (u32)(((dm->cur_rx_ok_cnt) >> 18) >>
			  1); /* <<3(8bit), >>20(10^6,M), >>1(2sec)*/
	dm->total_tp = dm->tx_tp + dm->rx_tp;

	dm->pre_traffic_load = dm->traffic_load;

	if (dm->cur_tx_ok_cnt > 1875000 ||
	    dm->cur_rx_ok_cnt >
		    1875000) { /* ( 1.875M * 8bit ) / 2sec= 7.5M bits /sec )*/

		dm->traffic_load = TRAFFIC_HIGH;
		/**/
	} else if (
		dm->cur_tx_ok_cnt > 500000 ||
		dm->cur_rx_ok_cnt >
			500000) { /*( 0.5M * 8bit ) / 2sec =  2M bits /sec )*/

		dm->traffic_load = TRAFFIC_MID;
		/**/
	} else if (
		dm->cur_tx_ok_cnt > 100000 ||
		dm->cur_rx_ok_cnt >
			100000) { /*( 0.1M * 8bit ) / 2sec =  0.4M bits /sec )*/

		dm->traffic_load = TRAFFIC_LOW;
		/**/
	} else {
		dm->traffic_load = TRAFFIC_ULTRA_LOW;
		/**/
	}
}