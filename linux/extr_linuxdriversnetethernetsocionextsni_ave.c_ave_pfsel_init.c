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
struct net_device {unsigned char* dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AVE_PFNUM_BROADCAST ; 
 int /*<<< orphan*/  AVE_PFNUM_FILTER ; 
 int /*<<< orphan*/  AVE_PFNUM_UNICAST ; 
 int AVE_PF_SIZE ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  ave_pfsel_set_macaddr (struct net_device*,int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  ave_pfsel_set_promisc (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ave_pfsel_stop (struct net_device*,int) ; 
 int /*<<< orphan*/  eth_broadcast_addr (unsigned char*) ; 

__attribute__((used)) static void ave_pfsel_init(struct net_device *ndev)
{
	unsigned char bcast_mac[ETH_ALEN];
	int i;

	eth_broadcast_addr(bcast_mac);

	for (i = 0; i < AVE_PF_SIZE; i++)
		ave_pfsel_stop(ndev, i);

	/* promiscious entry, select ring 0 */
	ave_pfsel_set_promisc(ndev, AVE_PFNUM_FILTER, 0);

	/* unicast entry */
	ave_pfsel_set_macaddr(ndev, AVE_PFNUM_UNICAST, ndev->dev_addr, 6);

	/* broadcast entry */
	ave_pfsel_set_macaddr(ndev, AVE_PFNUM_BROADCAST, bcast_mac, 6);
}