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
struct nf_conntrack_l4proto {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nf_ct_l4proto_pernet_unregister_one (struct net*,struct nf_conntrack_l4proto const* const) ; 

void nf_ct_l4proto_pernet_unregister(struct net *net,
				const struct nf_conntrack_l4proto *const l4proto[],
				unsigned int num_proto)
{
	while (num_proto-- != 0)
		nf_ct_l4proto_pernet_unregister_one(net, l4proto[num_proto]);
}