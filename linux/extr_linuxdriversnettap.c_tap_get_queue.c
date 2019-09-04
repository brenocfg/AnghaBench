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
struct tap_queue {int dummy; } ;
struct tap_dev {int /*<<< orphan*/ * taps; int /*<<< orphan*/  numvtaps; } ;
struct sk_buff {int dummy; } ;
typedef  int __u32 ;

/* Variables and functions */
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 struct tap_queue* rcu_dereference (int /*<<< orphan*/ ) ; 
 int skb_get_hash (struct sk_buff*) ; 
 int skb_get_rx_queue (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_rx_queue_recorded (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct tap_queue *tap_get_queue(struct tap_dev *tap,
				       struct sk_buff *skb)
{
	struct tap_queue *queue = NULL;
	/* Access to taps array is protected by rcu, but access to numvtaps
	 * isn't. Below we use it to lookup a queue, but treat it as a hint
	 * and validate that the result isn't NULL - in case we are
	 * racing against queue removal.
	 */
	int numvtaps = READ_ONCE(tap->numvtaps);
	__u32 rxq;

	if (!numvtaps)
		goto out;

	if (numvtaps == 1)
		goto single;

	/* Check if we can use flow to select a queue */
	rxq = skb_get_hash(skb);
	if (rxq) {
		queue = rcu_dereference(tap->taps[rxq % numvtaps]);
		goto out;
	}

	if (likely(skb_rx_queue_recorded(skb))) {
		rxq = skb_get_rx_queue(skb);

		while (unlikely(rxq >= numvtaps))
			rxq -= numvtaps;

		queue = rcu_dereference(tap->taps[rxq]);
		goto out;
	}

single:
	queue = rcu_dereference(tap->taps[0]);
out:
	return queue;
}