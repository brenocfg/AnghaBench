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
struct sk_buff {TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  xdp_prog; } ;

/* Variables and functions */
 int NET_RX_DROP ; 
 int NET_RX_SUCCESS ; 
 int XDP_PASS ; 
 int __netif_receive_skb (struct sk_buff*) ; 
 int do_xdp_generic (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  generic_xdp_needed_key ; 
 int /*<<< orphan*/  net_timestamp_check (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  netdev_tstamp_prequeue ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ skb_defer_rx_timestamp (struct sk_buff*) ; 
 scalar_t__ static_branch_unlikely (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int netif_receive_skb_internal(struct sk_buff *skb)
{
	int ret;

	net_timestamp_check(netdev_tstamp_prequeue, skb);

	if (skb_defer_rx_timestamp(skb))
		return NET_RX_SUCCESS;

	if (static_branch_unlikely(&generic_xdp_needed_key)) {
		int ret;

		preempt_disable();
		rcu_read_lock();
		ret = do_xdp_generic(rcu_dereference(skb->dev->xdp_prog), skb);
		rcu_read_unlock();
		preempt_enable();

		if (ret != XDP_PASS)
			return NET_RX_DROP;
	}

	rcu_read_lock();
#ifdef CONFIG_RPS
	if (static_key_false(&rps_needed)) {
		struct rps_dev_flow voidflow, *rflow = &voidflow;
		int cpu = get_rps_cpu(skb->dev, skb, &rflow);

		if (cpu >= 0) {
			ret = enqueue_to_backlog(skb, cpu, &rflow->last_qtail);
			rcu_read_unlock();
			return ret;
		}
	}
#endif
	ret = __netif_receive_skb(skb);
	rcu_read_unlock();
	return ret;
}