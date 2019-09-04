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
 int /*<<< orphan*/  audit_retry_queue ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 

__attribute__((used)) static void kauditd_retry_skb(struct sk_buff *skb)
{
	/* NOTE: because records should only live in the retry queue for a
	 * short period of time, before either being sent or moved to the hold
	 * queue, we don't currently enforce a limit on this queue */
	skb_queue_tail(&audit_retry_queue, skb);
}