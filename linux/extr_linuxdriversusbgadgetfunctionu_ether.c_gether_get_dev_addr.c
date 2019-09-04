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
struct net_device {int dummy; } ;
struct eth_dev {int /*<<< orphan*/  dev_mac; } ;

/* Variables and functions */
 int get_ether_addr_str (int /*<<< orphan*/ ,char*,int) ; 
 struct eth_dev* netdev_priv (struct net_device*) ; 

int gether_get_dev_addr(struct net_device *net, char *dev_addr, int len)
{
	struct eth_dev *dev;
	int ret;

	dev = netdev_priv(net);
	ret = get_ether_addr_str(dev->dev_mac, dev_addr, len);
	if (ret + 1 < len) {
		dev_addr[ret++] = '\n';
		dev_addr[ret] = '\0';
	}

	return ret;
}