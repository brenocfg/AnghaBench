#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int /*<<< orphan*/  next; int /*<<< orphan*/  users; } ;
typedef  enum skb_free_reason { ____Placeholder_skb_free_reason } skb_free_reason ;
struct TYPE_4__ {int reason; } ;
struct TYPE_3__ {int /*<<< orphan*/  completion_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  NET_TX_SOFTIRQ ; 
 int /*<<< orphan*/  __this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __this_cpu_write (int /*<<< orphan*/ ,struct sk_buff*) ; 
 TYPE_2__* get_kfree_skb_cb (struct sk_buff*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  raise_softirq_irqoff (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int refcount_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 TYPE_1__ softnet_data ; 
 scalar_t__ unlikely (int) ; 

void __dev_kfree_skb_irq(struct sk_buff *skb, enum skb_free_reason reason)
{
	unsigned long flags;

	if (unlikely(!skb))
		return;

	if (likely(refcount_read(&skb->users) == 1)) {
		smp_rmb();
		refcount_set(&skb->users, 0);
	} else if (likely(!refcount_dec_and_test(&skb->users))) {
		return;
	}
	get_kfree_skb_cb(skb)->reason = reason;
	local_irq_save(flags);
	skb->next = __this_cpu_read(softnet_data.completion_queue);
	__this_cpu_write(softnet_data.completion_queue, skb);
	raise_softirq_irqoff(NET_TX_SOFTIRQ);
	local_irq_restore(flags);
}