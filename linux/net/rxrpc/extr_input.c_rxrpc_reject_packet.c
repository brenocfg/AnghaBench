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
struct rxrpc_local {int /*<<< orphan*/  reject_queue; int /*<<< orphan*/  usage; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_SLAB_OKAY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rxrpc_free_skb (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ rxrpc_get_local_maybe (struct rxrpc_local*) ; 
 int /*<<< orphan*/  rxrpc_queue_local (struct rxrpc_local*) ; 
 int /*<<< orphan*/  rxrpc_skb_freed ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 

__attribute__((used)) static void rxrpc_reject_packet(struct rxrpc_local *local, struct sk_buff *skb)
{
	CHECK_SLAB_OKAY(&local->usage);

	if (rxrpc_get_local_maybe(local)) {
		skb_queue_tail(&local->reject_queue, skb);
		rxrpc_queue_local(local);
	} else {
		rxrpc_free_skb(skb, rxrpc_skb_freed);
	}
}