#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct nf_proto_net {int /*<<< orphan*/  users; } ;
struct net {int dummy; } ;
struct TYPE_5__ {int (* init_net ) (struct net*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  l3proto; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  builtin_l4proto ; 
 TYPE_1__ nf_conntrack_l4proto_generic ; 
 struct nf_proto_net* nf_ct_l4proto_net (struct net*,TYPE_1__*) ; 
 int nf_ct_l4proto_pernet_register (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nf_ct_l4proto_register_sysctl (struct net*,struct nf_proto_net*,TYPE_1__*) ; 
 int /*<<< orphan*/  nf_ct_l4proto_unregister_sysctl (struct net*,struct nf_proto_net*,TYPE_1__*) ; 
 int stub1 (struct net*,int /*<<< orphan*/ ) ; 

int nf_conntrack_proto_pernet_init(struct net *net)
{
	int err;
	struct nf_proto_net *pn = nf_ct_l4proto_net(net,
					&nf_conntrack_l4proto_generic);

	err = nf_conntrack_l4proto_generic.init_net(net,
					nf_conntrack_l4proto_generic.l3proto);
	if (err < 0)
		return err;
	err = nf_ct_l4proto_register_sysctl(net,
					    pn,
					    &nf_conntrack_l4proto_generic);
	if (err < 0)
		return err;

	err = nf_ct_l4proto_pernet_register(net, builtin_l4proto,
					    ARRAY_SIZE(builtin_l4proto));
	if (err < 0) {
		nf_ct_l4proto_unregister_sysctl(net, pn,
						&nf_conntrack_l4proto_generic);
		return err;
	}

	pn->users++;
	return 0;
}