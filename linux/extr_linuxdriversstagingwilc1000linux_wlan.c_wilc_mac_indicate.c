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
struct wilc {int mac_status; int /*<<< orphan*/  sync_event; } ;

/* Variables and functions */
 int MAC_STATUS_INIT ; 
 int /*<<< orphan*/  WID_STATUS ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wilc_wlan_cfg_get_val (int /*<<< orphan*/ ,unsigned char*,int) ; 

void wilc_mac_indicate(struct wilc *wilc)
{
	int status;

	wilc_wlan_cfg_get_val(WID_STATUS, (unsigned char *)&status, 4);
	if (wilc->mac_status == MAC_STATUS_INIT) {
		wilc->mac_status = status;
		complete(&wilc->sync_event);
	} else {
		wilc->mac_status = status;
	}
}