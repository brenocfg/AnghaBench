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

/* Variables and functions */

void odm_mac_status_query(struct phy_dm_struct *dm, u8 *mac_status, u8 mac_id,
			  bool is_packet_match_bssid, bool is_packet_to_self,
			  bool is_packet_beacon)
{
	/* 2011/10/19 Driver team will handle in the future. */
}