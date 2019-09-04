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
struct net_device {int dummy; } ;
struct mwifiex_private {int dummy; } ;

/* Variables and functions */
 struct mwifiex_private* mwifiex_netdev_get_priv (struct net_device*) ; 
 int mwifiex_set_mac_address (struct mwifiex_private*,struct net_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mwifiex_ndo_set_mac_address(struct net_device *dev, void *addr)
{
	struct mwifiex_private *priv = mwifiex_netdev_get_priv(dev);
	struct sockaddr *hw_addr = addr;

	return mwifiex_set_mac_address(priv, dev, true, hw_addr->sa_data);
}