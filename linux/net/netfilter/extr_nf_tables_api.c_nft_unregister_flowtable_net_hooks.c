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
struct net {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  nf_unregister_net_hook (struct net*,TYPE_1__*) ; 

__attribute__((used)) static void nft_unregister_flowtable_net_hooks(struct net *net,
					       struct nft_flowtable *flowtable)
{
	int i;

	for (i = 0; i < flowtable->ops_len; i++) {
		if (!flowtable->ops[i].dev)
			continue;

		nf_unregister_net_hook(net, &flowtable->ops[i]);
	}
}