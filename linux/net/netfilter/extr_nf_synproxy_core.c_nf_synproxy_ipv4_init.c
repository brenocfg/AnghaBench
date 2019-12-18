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
struct synproxy_net {scalar_t__ hook_ref4; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipv4_synproxy_ops ; 
 int nf_register_net_hooks (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int nf_synproxy_ipv4_init(struct synproxy_net *snet, struct net *net)
{
	int err;

	if (snet->hook_ref4 == 0) {
		err = nf_register_net_hooks(net, ipv4_synproxy_ops,
					    ARRAY_SIZE(ipv4_synproxy_ops));
		if (err)
			return err;
	}

	snet->hook_ref4++;
	return 0;
}