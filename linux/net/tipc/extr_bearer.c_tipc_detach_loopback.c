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
struct tipc_net {int /*<<< orphan*/  loopback_pt; } ;
struct net {int /*<<< orphan*/  loopback_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_remove_pack (int /*<<< orphan*/ *) ; 
 struct tipc_net* tipc_net (struct net*) ; 

void tipc_detach_loopback(struct net *net)
{
	struct tipc_net *tn = tipc_net(net);

	dev_remove_pack(&tn->loopback_pt);
	dev_put(net->loopback_dev);
}