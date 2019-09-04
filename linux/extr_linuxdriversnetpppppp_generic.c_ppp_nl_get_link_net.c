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
struct ppp {struct net* ppp_net; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 struct ppp* netdev_priv (struct net_device const*) ; 

__attribute__((used)) static struct net *ppp_nl_get_link_net(const struct net_device *dev)
{
	struct ppp *ppp = netdev_priv(dev);

	return ppp->ppp_net;
}