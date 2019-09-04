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
struct TYPE_2__ {struct device* parent; } ;
struct net_device {int /*<<< orphan*/  addr_len; int /*<<< orphan*/ * dev_addr; int /*<<< orphan*/  addr_assign_type; TYPE_1__ dev; } ;
struct dpaa2_eth_priv {int /*<<< orphan*/  mc_token; int /*<<< orphan*/  mc_io; struct net_device* net_dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  NET_ADDR_PERM ; 
 int /*<<< orphan*/  dev_dbg_once (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int dpni_get_port_mac_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int dpni_get_primary_mac_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int dpni_set_primary_mac_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eth_hw_addr_random (struct net_device*) ; 
 int /*<<< orphan*/  ether_addr_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ is_zero_ether_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_mac_addr(struct dpaa2_eth_priv *priv)
{
	struct net_device *net_dev = priv->net_dev;
	struct device *dev = net_dev->dev.parent;
	u8 mac_addr[ETH_ALEN], dpni_mac_addr[ETH_ALEN];
	int err;

	/* Get firmware address, if any */
	err = dpni_get_port_mac_addr(priv->mc_io, 0, priv->mc_token, mac_addr);
	if (err) {
		dev_err(dev, "dpni_get_port_mac_addr() failed\n");
		return err;
	}

	/* Get DPNI attributes address, if any */
	err = dpni_get_primary_mac_addr(priv->mc_io, 0, priv->mc_token,
					dpni_mac_addr);
	if (err) {
		dev_err(dev, "dpni_get_primary_mac_addr() failed\n");
		return err;
	}

	/* First check if firmware has any address configured by bootloader */
	if (!is_zero_ether_addr(mac_addr)) {
		/* If the DPMAC addr != DPNI addr, update it */
		if (!ether_addr_equal(mac_addr, dpni_mac_addr)) {
			err = dpni_set_primary_mac_addr(priv->mc_io, 0,
							priv->mc_token,
							mac_addr);
			if (err) {
				dev_err(dev, "dpni_set_primary_mac_addr() failed\n");
				return err;
			}
		}
		memcpy(net_dev->dev_addr, mac_addr, net_dev->addr_len);
	} else if (is_zero_ether_addr(dpni_mac_addr)) {
		/* No MAC address configured, fill in net_dev->dev_addr
		 * with a random one
		 */
		eth_hw_addr_random(net_dev);
		dev_dbg_once(dev, "device(s) have all-zero hwaddr, replaced with random\n");

		err = dpni_set_primary_mac_addr(priv->mc_io, 0, priv->mc_token,
						net_dev->dev_addr);
		if (err) {
			dev_err(dev, "dpni_set_primary_mac_addr() failed\n");
			return err;
		}

		/* Override NET_ADDR_RANDOM set by eth_hw_addr_random(); for all
		 * practical purposes, this will be our "permanent" mac address,
		 * at least until the next reboot. This move will also permit
		 * register_netdevice() to properly fill up net_dev->perm_addr.
		 */
		net_dev->addr_assign_type = NET_ADDR_PERM;
	} else {
		/* NET_ADDR_PERM is default, all we have to do is
		 * fill in the device addr.
		 */
		memcpy(net_dev->dev_addr, dpni_mac_addr, net_dev->addr_len);
	}

	return 0;
}