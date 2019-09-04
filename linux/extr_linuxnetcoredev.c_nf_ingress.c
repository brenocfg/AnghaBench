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
struct sk_buff {int dummy; } ;
struct packet_type {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline int nf_ingress(struct sk_buff *skb, struct packet_type **pt_prev,
			     int *ret, struct net_device *orig_dev)
{
#ifdef CONFIG_NETFILTER_INGRESS
	if (nf_hook_ingress_active(skb)) {
		int ingress_retval;

		if (*pt_prev) {
			*ret = deliver_skb(skb, *pt_prev, orig_dev);
			*pt_prev = NULL;
		}

		rcu_read_lock();
		ingress_retval = nf_hook_ingress(skb);
		rcu_read_unlock();
		return ingress_retval;
	}
#endif /* CONFIG_NETFILTER_INGRESS */
	return 0;
}