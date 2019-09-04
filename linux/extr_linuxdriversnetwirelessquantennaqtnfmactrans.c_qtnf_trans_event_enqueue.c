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
struct qtnf_qlink_transport {scalar_t__ event_queue_max_len; int /*<<< orphan*/  event_queue; } ;
struct qtnf_bus {int /*<<< orphan*/  event_work; int /*<<< orphan*/  workqueue; struct qtnf_qlink_transport trans; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 

__attribute__((used)) static int qtnf_trans_event_enqueue(struct qtnf_bus *bus, struct sk_buff *skb)
{
	struct qtnf_qlink_transport *trans = &bus->trans;

	if (likely(skb_queue_len(&trans->event_queue) <
		   trans->event_queue_max_len)) {
		skb_queue_tail(&trans->event_queue, skb);
		queue_work(bus->workqueue, &bus->event_work);
	} else {
		pr_warn("event dropped due to queue overflow\n");
		dev_kfree_skb(skb);
		return -1;
	}

	return 0;
}