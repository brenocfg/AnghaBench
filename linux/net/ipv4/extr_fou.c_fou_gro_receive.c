#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  gro_receive; } ;
struct net_offload {TYPE_1__ callbacks; } ;
struct list_head {int dummy; } ;
struct TYPE_6__ {int is_fou; scalar_t__ is_ipv6; scalar_t__ encap_mark; } ;
struct TYPE_5__ {size_t protocol; } ;

/* Variables and functions */
 TYPE_3__* NAPI_GRO_CB (struct sk_buff*) ; 
 struct sk_buff* call_gro_receive (int /*<<< orphan*/ ,struct list_head*,struct sk_buff*) ; 
 TYPE_2__* fou_from_sock (struct sock*) ; 
 struct net_offload** inet6_offloads ; 
 struct net_offload** inet_offloads ; 
 struct net_offload* rcu_dereference (struct net_offload const*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static struct sk_buff *fou_gro_receive(struct sock *sk,
				       struct list_head *head,
				       struct sk_buff *skb)
{
	u8 proto = fou_from_sock(sk)->protocol;
	const struct net_offload **offloads;
	const struct net_offload *ops;
	struct sk_buff *pp = NULL;

	/* We can clear the encap_mark for FOU as we are essentially doing
	 * one of two possible things.  We are either adding an L4 tunnel
	 * header to the outer L3 tunnel header, or we are are simply
	 * treating the GRE tunnel header as though it is a UDP protocol
	 * specific header such as VXLAN or GENEVE.
	 */
	NAPI_GRO_CB(skb)->encap_mark = 0;

	/* Flag this frame as already having an outer encap header */
	NAPI_GRO_CB(skb)->is_fou = 1;

	rcu_read_lock();
	offloads = NAPI_GRO_CB(skb)->is_ipv6 ? inet6_offloads : inet_offloads;
	ops = rcu_dereference(offloads[proto]);
	if (!ops || !ops->callbacks.gro_receive)
		goto out_unlock;

	pp = call_gro_receive(ops->callbacks.gro_receive, head, skb);

out_unlock:
	rcu_read_unlock();

	return pp;
}