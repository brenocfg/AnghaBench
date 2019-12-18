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
struct TYPE_2__ {int /*<<< orphan*/  func; int /*<<< orphan*/  type; struct net_device* dev; } ;
struct tipc_net {TYPE_1__ loopback_pt; } ;
struct net_device {int dummy; } ;
struct net {struct net_device* loopback_dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  ETH_P_TIPC ; 
 int /*<<< orphan*/  dev_add_pack (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_loopback_rcv_pkt ; 
 struct tipc_net* tipc_net (struct net*) ; 

int tipc_attach_loopback(struct net *net)
{
	struct net_device *dev = net->loopback_dev;
	struct tipc_net *tn = tipc_net(net);

	if (!dev)
		return -ENODEV;

	dev_hold(dev);
	tn->loopback_pt.dev = dev;
	tn->loopback_pt.type = htons(ETH_P_TIPC);
	tn->loopback_pt.func = tipc_loopback_rcv_pkt;
	dev_add_pack(&tn->loopback_pt);
	return 0;
}