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
typedef  struct sk_buff sk_buff ;

/* Variables and functions */
 int /*<<< orphan*/  __vsock_deliver_tap (struct sk_buff*) ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  vsock_tap_all ; 

void vsock_deliver_tap(struct sk_buff *build_skb(void *opaque), void *opaque)
{
	struct sk_buff *skb;

	rcu_read_lock();

	if (likely(list_empty(&vsock_tap_all)))
		goto out;

	skb = build_skb(opaque);
	if (skb) {
		__vsock_deliver_tap(skb);
		consume_skb(skb);
	}

out:
	rcu_read_unlock();
}