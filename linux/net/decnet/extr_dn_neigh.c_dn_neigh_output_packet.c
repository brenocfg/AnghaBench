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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct net {int dummy; } ;
struct neighbour {int (* output ) (struct neighbour*,struct sk_buff*) ;} ;
struct dst_entry {int dummy; } ;
struct dn_route {struct neighbour* n; } ;

/* Variables and functions */
 struct dst_entry* skb_dst (struct sk_buff*) ; 
 int stub1 (struct neighbour*,struct sk_buff*) ; 

__attribute__((used)) static int dn_neigh_output_packet(struct net *net, struct sock *sk, struct sk_buff *skb)
{
	struct dst_entry *dst = skb_dst(skb);
	struct dn_route *rt = (struct dn_route *)dst;
	struct neighbour *neigh = rt->n;

	return neigh->output(neigh, skb);
}