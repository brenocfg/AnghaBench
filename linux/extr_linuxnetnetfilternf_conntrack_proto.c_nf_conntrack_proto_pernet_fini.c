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
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  builtin_l4proto ; 
 int /*<<< orphan*/  nf_conntrack_l4proto_generic ; 
 struct nf_proto_net* nf_ct_l4proto_net (struct net*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nf_ct_l4proto_pernet_unregister (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_ct_l4proto_unregister_sysctl (struct net*,struct nf_proto_net*,int /*<<< orphan*/ *) ; 

void nf_conntrack_proto_pernet_fini(struct net *net)
{
	struct nf_proto_net *pn = nf_ct_l4proto_net(net,
					&nf_conntrack_l4proto_generic);

	nf_ct_l4proto_pernet_unregister(net, builtin_l4proto,
					ARRAY_SIZE(builtin_l4proto));
	pn->users--;
	nf_ct_l4proto_unregister_sysctl(net,
					pn,
					&nf_conntrack_l4proto_generic);
}