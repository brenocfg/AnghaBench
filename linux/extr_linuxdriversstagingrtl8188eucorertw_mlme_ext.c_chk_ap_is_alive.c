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
struct sta_info {int dummy; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 scalar_t__ sta_last_rx_beacon_pkts (struct sta_info*) ; 
 scalar_t__ sta_last_rx_data_pkts (struct sta_info*) ; 
 scalar_t__ sta_last_rx_probersp_pkts (struct sta_info*) ; 
 scalar_t__ sta_rx_beacon_pkts (struct sta_info*) ; 
 scalar_t__ sta_rx_data_pkts (struct sta_info*) ; 
 scalar_t__ sta_rx_probersp_pkts (struct sta_info*) ; 
 int /*<<< orphan*/  sta_update_last_rx_pkts (struct sta_info*) ; 

__attribute__((used)) static u8 chk_ap_is_alive(struct adapter *padapter, struct sta_info *psta)
{
	u8 ret = false;

	if ((sta_rx_data_pkts(psta) == sta_last_rx_data_pkts(psta)) &&
	    sta_rx_beacon_pkts(psta) == sta_last_rx_beacon_pkts(psta) &&
	    sta_rx_probersp_pkts(psta) == sta_last_rx_probersp_pkts(psta))
		ret = false;
	else
		ret = true;

	sta_update_last_rx_pkts(psta);

	return ret;
}