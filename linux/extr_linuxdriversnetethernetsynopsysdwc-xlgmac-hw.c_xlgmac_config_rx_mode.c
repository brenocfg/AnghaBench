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
struct xlgmac_pdata {struct net_device* netdev; } ;
struct net_device {int flags; } ;

/* Variables and functions */
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  xlgmac_add_mac_addresses (struct xlgmac_pdata*) ; 
 int /*<<< orphan*/  xlgmac_set_all_multicast_mode (struct xlgmac_pdata*,unsigned int) ; 
 int /*<<< orphan*/  xlgmac_set_promiscuous_mode (struct xlgmac_pdata*,unsigned int) ; 

__attribute__((used)) static int xlgmac_config_rx_mode(struct xlgmac_pdata *pdata)
{
	struct net_device *netdev = pdata->netdev;
	unsigned int pr_mode, am_mode;

	pr_mode = ((netdev->flags & IFF_PROMISC) != 0);
	am_mode = ((netdev->flags & IFF_ALLMULTI) != 0);

	xlgmac_set_promiscuous_mode(pdata, pr_mode);
	xlgmac_set_all_multicast_mode(pdata, am_mode);

	xlgmac_add_mac_addresses(pdata);

	return 0;
}