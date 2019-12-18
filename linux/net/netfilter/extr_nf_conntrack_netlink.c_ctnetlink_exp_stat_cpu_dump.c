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
struct sk_buff {int len; int /*<<< orphan*/  sk; } ;
struct netlink_callback {int* args; TYPE_2__* nlh; int /*<<< orphan*/  skb; } ;
struct TYPE_4__ {int /*<<< orphan*/  stat; } ;
struct net {TYPE_1__ ct; } ;
struct ip_conntrack_stat {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  portid; } ;
struct TYPE_5__ {int /*<<< orphan*/  nlmsg_seq; } ;

/* Variables and functions */
 TYPE_3__ NETLINK_CB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_possible (int) ; 
 scalar_t__ ctnetlink_exp_stat_fill_info (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct ip_conntrack_stat const*) ; 
 int nr_cpu_ids ; 
 struct ip_conntrack_stat* per_cpu_ptr (int /*<<< orphan*/ ,int) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ctnetlink_exp_stat_cpu_dump(struct sk_buff *skb, struct netlink_callback *cb)
{
	int cpu;
	struct net *net = sock_net(skb->sk);

	if (cb->args[0] == nr_cpu_ids)
		return 0;

	for (cpu = cb->args[0]; cpu < nr_cpu_ids; cpu++) {
		const struct ip_conntrack_stat *st;

		if (!cpu_possible(cpu))
			continue;

		st = per_cpu_ptr(net->ct.stat, cpu);
		if (ctnetlink_exp_stat_fill_info(skb, NETLINK_CB(cb->skb).portid,
						 cb->nlh->nlmsg_seq,
						 cpu, st) < 0)
			break;
	}
	cb->args[0] = cpu;

	return skb->len;
}