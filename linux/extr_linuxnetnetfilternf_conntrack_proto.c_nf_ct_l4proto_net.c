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
struct nf_proto_net {int dummy; } ;
struct nf_conntrack_l4proto {int /*<<< orphan*/ * net_id; struct nf_proto_net* (* get_net_proto ) (struct net*) ;} ;
struct net {int dummy; } ;

/* Variables and functions */
 struct nf_proto_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 struct nf_proto_net* stub1 (struct net*) ; 

__attribute__((used)) static struct nf_proto_net *nf_ct_l4proto_net(struct net *net,
				const struct nf_conntrack_l4proto *l4proto)
{
	if (l4proto->get_net_proto) {
		/* statically built-in protocols use static per-net */
		return l4proto->get_net_proto(net);
	} else if (l4proto->net_id) {
		/* ... and loadable protocols use dynamic per-net */
		return net_generic(net, *l4proto->net_id);
	}
	return NULL;
}