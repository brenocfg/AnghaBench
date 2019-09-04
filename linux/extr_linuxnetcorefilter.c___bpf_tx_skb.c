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
struct sk_buff {struct net_device* dev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int ENETDOWN ; 
 scalar_t__ XMIT_RECURSION_LIMIT ; 
 int /*<<< orphan*/  __this_cpu_dec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __this_cpu_inc (int /*<<< orphan*/ ) ; 
 scalar_t__ __this_cpu_read (int /*<<< orphan*/ ) ; 
 int dev_queue_xmit (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  net_crit_ratelimited (char*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  xmit_recursion ; 

__attribute__((used)) static inline int __bpf_tx_skb(struct net_device *dev, struct sk_buff *skb)
{
	int ret;

	if (unlikely(__this_cpu_read(xmit_recursion) > XMIT_RECURSION_LIMIT)) {
		net_crit_ratelimited("bpf: recursion limit reached on datapath, buggy bpf program?\n");
		kfree_skb(skb);
		return -ENETDOWN;
	}

	skb->dev = dev;

	__this_cpu_inc(xmit_recursion);
	ret = dev_queue_xmit(skb);
	__this_cpu_dec(xmit_recursion);

	return ret;
}