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

/* Variables and functions */
 int __netif_receive_skb_one_core (struct sk_buff*,int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

int netif_receive_skb_core(struct sk_buff *skb)
{
	int ret;

	rcu_read_lock();
	ret = __netif_receive_skb_one_core(skb, false);
	rcu_read_unlock();

	return ret;
}