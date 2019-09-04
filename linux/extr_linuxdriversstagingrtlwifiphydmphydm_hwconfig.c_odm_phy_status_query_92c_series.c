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
struct phy_dm_struct {int dummy; } ;
struct dm_phy_status_info {int dummy; } ;
struct dm_per_pkt_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  odm_process_rssi_for_dm (struct phy_dm_struct*,struct dm_phy_status_info*,struct dm_per_pkt_info*) ; 
 int /*<<< orphan*/  odm_rx_phy_status92c_series_parsing (struct phy_dm_struct*,struct dm_phy_status_info*,int /*<<< orphan*/ *,struct dm_per_pkt_info*) ; 

__attribute__((used)) static void odm_phy_status_query_92c_series(struct phy_dm_struct *dm,
					    struct dm_phy_status_info *phy_info,
					    u8 *phy_status,
					    struct dm_per_pkt_info *pktinfo)
{
	odm_rx_phy_status92c_series_parsing(dm, phy_info, phy_status, pktinfo);
	odm_process_rssi_for_dm(dm, phy_info, pktinfo);
}