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
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct r8152 {scalar_t__ version; struct net_device* netdev; } ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  PLA_BACKUP ; 
 int /*<<< orphan*/  PLA_IDR ; 
 scalar_t__ RTL_VER_01 ; 
 int /*<<< orphan*/  eth_hw_addr_random (struct net_device*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_err (struct r8152*,int /*<<< orphan*/ ,struct net_device*,char*,...) ; 
 int /*<<< orphan*/  netif_info (struct r8152*,int /*<<< orphan*/ ,struct net_device*,char*,int /*<<< orphan*/ ) ; 
 int pla_ocp_read (struct r8152*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  probe ; 
 int rtl8152_set_mac_address (struct net_device*,struct sockaddr*) ; 
 int vendor_mac_passthru_addr_read (struct r8152*,struct sockaddr*) ; 

__attribute__((used)) static int set_ethernet_addr(struct r8152 *tp)
{
	struct net_device *dev = tp->netdev;
	struct sockaddr sa;
	int ret;

	if (tp->version == RTL_VER_01) {
		ret = pla_ocp_read(tp, PLA_IDR, 8, sa.sa_data);
	} else {
		/* if this is not an RTL8153-AD, no eFuse mac pass thru set,
		 * or system doesn't provide valid _SB.AMAC this will be
		 * be expected to non-zero
		 */
		ret = vendor_mac_passthru_addr_read(tp, &sa);
		if (ret < 0)
			ret = pla_ocp_read(tp, PLA_BACKUP, 8, sa.sa_data);
	}

	if (ret < 0) {
		netif_err(tp, probe, dev, "Get ether addr fail\n");
	} else if (!is_valid_ether_addr(sa.sa_data)) {
		netif_err(tp, probe, dev, "Invalid ether addr %pM\n",
			  sa.sa_data);
		eth_hw_addr_random(dev);
		ether_addr_copy(sa.sa_data, dev->dev_addr);
		ret = rtl8152_set_mac_address(dev, &sa);
		netif_info(tp, probe, dev, "Random ether addr %pM\n",
			   sa.sa_data);
	} else {
		if (tp->version == RTL_VER_01)
			ether_addr_copy(dev->dev_addr, sa.sa_data);
		else
			ret = rtl8152_set_mac_address(dev, &sa);
	}

	return ret;
}