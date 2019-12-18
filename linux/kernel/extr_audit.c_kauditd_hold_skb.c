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
 scalar_t__ audit_backlog_limit ; 
 int /*<<< orphan*/  audit_default ; 
 int /*<<< orphan*/  audit_hold_queue ; 
 int /*<<< orphan*/  audit_log_lost (char*) ; 
 int /*<<< orphan*/  kauditd_printk_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 

__attribute__((used)) static void kauditd_hold_skb(struct sk_buff *skb)
{
	/* at this point it is uncertain if we will ever send this to auditd so
	 * try to send the message via printk before we go any further */
	kauditd_printk_skb(skb);

	/* can we just silently drop the message? */
	if (!audit_default) {
		kfree_skb(skb);
		return;
	}

	/* if we have room, queue the message */
	if (!audit_backlog_limit ||
	    skb_queue_len(&audit_hold_queue) < audit_backlog_limit) {
		skb_queue_tail(&audit_hold_queue, skb);
		return;
	}

	/* we have no other options - drop the message */
	audit_log_lost("kauditd hold queue overflow");
	kfree_skb(skb);
}