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
struct tcf_action_net {int /*<<< orphan*/  egdev_ht; } ;
struct tcf_action_egdev {int dummy; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 struct net* dev_net (struct net_device const*) ; 
 struct tcf_action_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 struct tcf_action_egdev* rhashtable_lookup_fast (int /*<<< orphan*/ *,struct net_device const**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcf_action_egdev_ht_params ; 
 int /*<<< orphan*/  tcf_action_net_id ; 

__attribute__((used)) static struct tcf_action_egdev *
tcf_action_egdev_lookup(const struct net_device *dev)
{
	struct net *net = dev_net(dev);
	struct tcf_action_net *tan = net_generic(net, tcf_action_net_id);

	return rhashtable_lookup_fast(&tan->egdev_ht, &dev,
				      tcf_action_egdev_ht_params);
}