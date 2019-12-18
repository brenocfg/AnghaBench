#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int pf; } ;
struct nf_queue_entry {TYPE_1__ state; } ;
struct nf_ipv6_ops {int (* reroute ) (struct sk_buff*,struct nf_queue_entry*) ;} ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int nf_ip_reroute (struct sk_buff*,struct nf_queue_entry*) ; 
 int /*<<< orphan*/  nf_ipv6_ops ; 
 struct nf_ipv6_ops* rcu_dereference (int /*<<< orphan*/ ) ; 
 int stub1 (struct sk_buff*,struct nf_queue_entry*) ; 

int nf_reroute(struct sk_buff *skb, struct nf_queue_entry *entry)
{
	const struct nf_ipv6_ops *v6ops;
	int ret = 0;

	switch (entry->state.pf) {
	case AF_INET:
		ret = nf_ip_reroute(skb, entry);
		break;
	case AF_INET6:
		v6ops = rcu_dereference(nf_ipv6_ops);
		if (v6ops)
			ret = v6ops->reroute(skb, entry);
		break;
	}
	return ret;
}