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
struct rtllib_device {int /*<<< orphan*/  crypt_info; int /*<<< orphan*/ * pHTInfo; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lib80211_crypt_info_free (int /*<<< orphan*/ *) ; 
 scalar_t__ netdev_priv_rsl (struct net_device*) ; 
 int /*<<< orphan*/  rtllib_networks_free (struct rtllib_device*) ; 
 int /*<<< orphan*/  rtllib_softmac_free (struct rtllib_device*) ; 

void free_rtllib(struct net_device *dev)
{
	struct rtllib_device *ieee = (struct rtllib_device *)
				      netdev_priv_rsl(dev);

	kfree(ieee->pHTInfo);
	ieee->pHTInfo = NULL;
	rtllib_softmac_free(ieee);

	lib80211_crypt_info_free(&ieee->crypt_info);

	rtllib_networks_free(ieee);
	free_netdev(dev);
}