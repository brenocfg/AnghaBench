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
struct nf_conntrack_l4proto {scalar_t__ l3proto; int /*<<< orphan*/  l4proto; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ PF_INET6 ; 
 int nf_ct_l4proto_pernet_register_one (struct net*,struct nf_conntrack_l4proto const* const) ; 
 int /*<<< orphan*/  nf_ct_l4proto_pernet_unregister (struct net*,struct nf_conntrack_l4proto const* const*,unsigned int) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 

int nf_ct_l4proto_pernet_register(struct net *net,
				  const struct nf_conntrack_l4proto *const l4proto[],
				  unsigned int num_proto)
{
	int ret = -EINVAL;
	unsigned int i;

	for (i = 0; i < num_proto; i++) {
		ret = nf_ct_l4proto_pernet_register_one(net, l4proto[i]);
		if (ret < 0)
			break;
	}
	if (i != num_proto) {
		pr_err("nf_conntrack_proto_%d %d: pernet registration failed\n",
		       l4proto[i]->l4proto,
		       l4proto[i]->l3proto == PF_INET6 ? 6 : 4);
		nf_ct_l4proto_pernet_unregister(net, l4proto, i);
	}
	return ret;
}