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
struct ip6_tnl {int dummy; } ;

/* Variables and functions */
 struct ip6_tnl* netdev_priv (struct net_device*) ; 
 int vti6_dev_init_gen (struct net_device*) ; 
 int /*<<< orphan*/  vti6_link_config (struct ip6_tnl*,int) ; 

__attribute__((used)) static int vti6_dev_init(struct net_device *dev)
{
	struct ip6_tnl *t = netdev_priv(dev);
	int err = vti6_dev_init_gen(dev);

	if (err)
		return err;
	vti6_link_config(t, true);
	return 0;
}