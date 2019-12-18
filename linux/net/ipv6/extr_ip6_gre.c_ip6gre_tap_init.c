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
struct net_device {int /*<<< orphan*/  priv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFF_LIVE_ADDR_CHANGE ; 
 int ip6gre_tunnel_init_common (struct net_device*) ; 

__attribute__((used)) static int ip6gre_tap_init(struct net_device *dev)
{
	int ret;

	ret = ip6gre_tunnel_init_common(dev);
	if (ret)
		return ret;

	dev->priv_flags |= IFF_LIVE_ADDR_CHANGE;

	return 0;
}