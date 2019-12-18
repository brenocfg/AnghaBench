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
struct net {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  kuid_t ;
typedef  int /*<<< orphan*/  kgid_t ;

/* Variables and functions */
 struct net* dev_net (struct net_device*) ; 
 int /*<<< orphan*/  net_ns_get_ownership (struct net const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct net_device* to_net_dev (struct device*) ; 

__attribute__((used)) static void net_get_ownership(struct device *d, kuid_t *uid, kgid_t *gid)
{
	struct net_device *dev = to_net_dev(d);
	const struct net *net = dev_net(dev);

	net_ns_get_ownership(net, uid, gid);
}