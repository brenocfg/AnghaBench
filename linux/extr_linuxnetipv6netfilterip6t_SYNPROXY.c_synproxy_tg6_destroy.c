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
struct xt_tgdtor_param {int /*<<< orphan*/  family; int /*<<< orphan*/  net; } ;
struct synproxy_net {scalar_t__ hook_ref6; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipv6_synproxy_ops ; 
 int /*<<< orphan*/  nf_ct_netns_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_unregister_net_hooks (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct synproxy_net* synproxy_pernet (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void synproxy_tg6_destroy(const struct xt_tgdtor_param *par)
{
	struct synproxy_net *snet = synproxy_pernet(par->net);

	snet->hook_ref6--;
	if (snet->hook_ref6 == 0)
		nf_unregister_net_hooks(par->net, ipv6_synproxy_ops,
					ARRAY_SIZE(ipv6_synproxy_ops));
	nf_ct_netns_put(par->net, par->family);
}