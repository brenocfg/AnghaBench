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
struct socket {int dummy; } ;
struct sk_buff {int dummy; } ;
struct rxrpc_call {scalar_t__ rx_hard_ack; int /*<<< orphan*/  user_mutex; struct sk_buff** rxtx_buffer; int /*<<< orphan*/  rx_top; int /*<<< orphan*/  state; } ;
typedef  scalar_t__ rxrpc_seq_t ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ RXRPC_CALL_CLIENT_RECV_REPLY ; 
 scalar_t__ RXRPC_RXTX_BUFF_MASK ; 
 scalar_t__ after (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_get_ktime (struct sk_buff*) ; 
 scalar_t__ smp_load_acquire (int /*<<< orphan*/ *) ; 

bool rxrpc_kernel_get_reply_time(struct socket *sock, struct rxrpc_call *call,
				 ktime_t *_ts)
{
	struct sk_buff *skb;
	rxrpc_seq_t hard_ack, top, seq;
	bool success = false;

	mutex_lock(&call->user_mutex);

	if (READ_ONCE(call->state) != RXRPC_CALL_CLIENT_RECV_REPLY)
		goto out;

	hard_ack = call->rx_hard_ack;
	if (hard_ack != 0)
		goto out;

	seq = hard_ack + 1;
	top = smp_load_acquire(&call->rx_top);
	if (after(seq, top))
		goto out;

	skb = call->rxtx_buffer[seq & RXRPC_RXTX_BUFF_MASK];
	if (!skb)
		goto out;

	*_ts = skb_get_ktime(skb);
	success = true;

out:
	mutex_unlock(&call->user_mutex);
	return success;
}