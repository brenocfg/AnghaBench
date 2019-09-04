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
struct usbnet {int dummy; } ;
struct net_device {int mtu; } ;

/* Variables and functions */
 scalar_t__ cdc_ncm_eth_hlen (struct usbnet*) ; 
 int /*<<< orphan*/  cdc_ncm_set_dgram_size (struct usbnet*,scalar_t__) ; 
 struct usbnet* netdev_priv (struct net_device*) ; 

int cdc_ncm_change_mtu(struct net_device *net, int new_mtu)
{
	struct usbnet *dev = netdev_priv(net);

	net->mtu = new_mtu;
	cdc_ncm_set_dgram_size(dev, new_mtu + cdc_ncm_eth_hlen(dev));

	return 0;
}