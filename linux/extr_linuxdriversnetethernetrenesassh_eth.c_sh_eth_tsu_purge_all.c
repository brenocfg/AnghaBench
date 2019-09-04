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
struct sh_eth_private {TYPE_1__* cd; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tsu; } ;

/* Variables and functions */
 int SH_ETH_TSU_CAM_ENTRIES ; 
 struct sh_eth_private* netdev_priv (struct net_device*) ; 
 scalar_t__ sh_eth_tsu_disable_cam_entry_post (struct net_device*,int) ; 
 int sh_eth_tsu_disable_cam_entry_table (struct net_device*,int) ; 

__attribute__((used)) static int sh_eth_tsu_purge_all(struct net_device *ndev)
{
	struct sh_eth_private *mdp = netdev_priv(ndev);
	int i, ret;

	if (!mdp->cd->tsu)
		return 0;

	for (i = 0; i < SH_ETH_TSU_CAM_ENTRIES; i++) {
		if (sh_eth_tsu_disable_cam_entry_post(ndev, i))
			continue;

		/* Disable the entry if both ports was disabled */
		ret = sh_eth_tsu_disable_cam_entry_table(ndev, i);
		if (ret < 0)
			return ret;
	}

	return 0;
}