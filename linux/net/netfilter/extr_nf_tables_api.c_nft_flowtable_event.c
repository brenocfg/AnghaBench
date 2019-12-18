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
struct nft_flowtable {int ops_len; TYPE_1__* ops; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {struct net_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int /*<<< orphan*/  nf_unregister_net_hook (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void nft_flowtable_event(unsigned long event, struct net_device *dev,
				struct nft_flowtable *flowtable)
{
	int i;

	for (i = 0; i < flowtable->ops_len; i++) {
		if (flowtable->ops[i].dev != dev)
			continue;

		nf_unregister_net_hook(dev_net(dev), &flowtable->ops[i]);
		flowtable->ops[i].dev = NULL;
		break;
	}
}