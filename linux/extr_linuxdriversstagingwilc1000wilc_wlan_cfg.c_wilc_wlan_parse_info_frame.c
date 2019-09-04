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
struct wilc_mac_cfg {int mac_status; } ;

/* Variables and functions */
 int WID_STATUS ; 
 int WILC_CFG_RSP_STATUS ; 
 struct wilc_mac_cfg g_mac ; 

__attribute__((used)) static int wilc_wlan_parse_info_frame(u8 *info, int size)
{
	struct wilc_mac_cfg *pd = &g_mac;
	u32 wid, len;
	int type = WILC_CFG_RSP_STATUS;

	wid = info[0] | (info[1] << 8);

	len = info[2];

	if (len == 1 && wid == WID_STATUS) {
		pd->mac_status = info[3];
		type = WILC_CFG_RSP_STATUS;
	}

	return type;
}