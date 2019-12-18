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
struct TYPE_4__ {int (* gro_complete ) (struct sk_buff*,int) ;} ;
struct net_offload {TYPE_1__ callbacks; } ;
struct TYPE_6__ {scalar_t__ is_ipv6; } ;
struct TYPE_5__ {size_t protocol; } ;

/* Variables and functions */
 int ENOSYS ; 
 TYPE_3__* NAPI_GRO_CB (struct sk_buff*) ; 
 scalar_t__ WARN_ON (int) ; 
 TYPE_2__* fou_from_sock (struct sock*) ; 
 struct net_offload** inet6_offloads ; 
 struct net_offload** inet_offloads ; 
 struct net_offload* rcu_dereference (struct net_offload const*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  skb_set_inner_mac_header (struct sk_buff*,int) ; 
 int stub1 (struct sk_buff*,int) ; 

__attribute__((used)) static int fou_gro_complete(struct sock *sk, struct sk_buff *skb,
			    int nhoff)
{
	const struct net_offload *ops;
	u8 proto = fou_from_sock(sk)->protocol;
	int err = -ENOSYS;
	const struct net_offload **offloads;

	rcu_read_lock();
	offloads = NAPI_GRO_CB(skb)->is_ipv6 ? inet6_offloads : inet_offloads;
	ops = rcu_dereference(offloads[proto]);
	if (WARN_ON(!ops || !ops->callbacks.gro_complete))
		goto out_unlock;

	err = ops->callbacks.gro_complete(skb, nhoff);

	skb_set_inner_mac_header(skb, nhoff);

out_unlock:
	rcu_read_unlock();

	return err;
}