#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct wilc {int vif_num; TYPE_1__** vif; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ mode; struct net_device* ndev; int /*<<< orphan*/  bssid; } ;

/* Variables and functions */
 scalar_t__ AP_MODE ; 
 scalar_t__ STATION_MODE ; 
 scalar_t__ ether_addr_equal_unaligned (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct net_device *get_if_handler(struct wilc *wilc, u8 *mac_header)
{
	u8 *bssid, *bssid1;
	int i = 0;

	bssid = mac_header + 10;
	bssid1 = mac_header + 4;

	for (i = 0; i < wilc->vif_num; i++) {
		if (wilc->vif[i]->mode == STATION_MODE)
			if (ether_addr_equal_unaligned(bssid,
						       wilc->vif[i]->bssid))
				return wilc->vif[i]->ndev;
		if (wilc->vif[i]->mode == AP_MODE)
			if (ether_addr_equal_unaligned(bssid1,
						       wilc->vif[i]->bssid))
				return wilc->vif[i]->ndev;
	}

	return NULL;
}