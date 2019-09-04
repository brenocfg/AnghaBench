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
struct net_bridge {int /*<<< orphan*/  dev; } ;
struct net {int /*<<< orphan*/  user_ns; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int EINVAL ; 
 int EPERM ; 
 struct net_device* __dev_get_by_index (struct net*,int) ; 
 int br_add_if (struct net_bridge*,struct net_device*,int /*<<< orphan*/ *) ; 
 int br_del_if (struct net_bridge*,struct net_device*) ; 
 struct net* dev_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ns_capable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int add_del_if(struct net_bridge *br, int ifindex, int isadd)
{
	struct net *net = dev_net(br->dev);
	struct net_device *dev;
	int ret;

	if (!ns_capable(net->user_ns, CAP_NET_ADMIN))
		return -EPERM;

	dev = __dev_get_by_index(net, ifindex);
	if (dev == NULL)
		return -EINVAL;

	if (isadd)
		ret = br_add_if(br, dev, NULL);
	else
		ret = br_del_if(br, dev);

	return ret;
}