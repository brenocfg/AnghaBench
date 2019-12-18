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
struct sk_buff {int /*<<< orphan*/  dev; } ;
struct rps_dev_flow {unsigned int last_qtail; } ;

/* Variables and functions */
 int enqueue_to_backlog (struct sk_buff*,int,unsigned int*) ; 
 int get_cpu () ; 
 int get_rps_cpu (int /*<<< orphan*/ ,struct sk_buff*,struct rps_dev_flow**) ; 
 int /*<<< orphan*/  net_timestamp_check (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  netdev_tstamp_prequeue ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  put_cpu () ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  rps_needed ; 
 int smp_processor_id () ; 
 scalar_t__ static_branch_unlikely (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_netif_rx (struct sk_buff*) ; 

__attribute__((used)) static int netif_rx_internal(struct sk_buff *skb)
{
	int ret;

	net_timestamp_check(netdev_tstamp_prequeue, skb);

	trace_netif_rx(skb);

#ifdef CONFIG_RPS
	if (static_branch_unlikely(&rps_needed)) {
		struct rps_dev_flow voidflow, *rflow = &voidflow;
		int cpu;

		preempt_disable();
		rcu_read_lock();

		cpu = get_rps_cpu(skb->dev, skb, &rflow);
		if (cpu < 0)
			cpu = smp_processor_id();

		ret = enqueue_to_backlog(skb, cpu, &rflow->last_qtail);

		rcu_read_unlock();
		preempt_enable();
	} else
#endif
	{
		unsigned int qtail;

		ret = enqueue_to_backlog(skb, get_cpu(), &qtail);
		put_cpu();
	}
	return ret;
}