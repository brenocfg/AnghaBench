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
struct nf_proto_net {int /*<<< orphan*/  users; } ;
struct nf_conntrack_l4proto {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 struct nf_proto_net* nf_ct_l4proto_net (struct net*,struct nf_conntrack_l4proto const*) ; 
 int /*<<< orphan*/  nf_ct_l4proto_unregister_sysctl (struct net*,struct nf_proto_net*,struct nf_conntrack_l4proto const*) ; 

void nf_ct_l4proto_pernet_unregister_one(struct net *net,
				const struct nf_conntrack_l4proto *l4proto)
{
	struct nf_proto_net *pn = nf_ct_l4proto_net(net, l4proto);

	if (pn == NULL)
		return;

	pn->users--;
	nf_ct_l4proto_unregister_sysctl(net, pn, l4proto);
}