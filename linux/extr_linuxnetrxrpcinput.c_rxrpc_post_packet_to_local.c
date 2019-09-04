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
struct rxrpc_local {int /*<<< orphan*/  event_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  _enter (char*,struct rxrpc_local*,struct sk_buff*) ; 
 int /*<<< orphan*/  rxrpc_queue_local (struct rxrpc_local*) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 

__attribute__((used)) static void rxrpc_post_packet_to_local(struct rxrpc_local *local,
				       struct sk_buff *skb)
{
	_enter("%p,%p", local, skb);

	skb_queue_tail(&local->event_queue, skb);
	rxrpc_queue_local(local);
}