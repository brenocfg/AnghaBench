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
struct socket {struct sock* sk; } ;
struct sock {scalar_t__ sk_state; int /*<<< orphan*/  sk_err; int /*<<< orphan*/  sk_receive_queue; } ;
struct sk_buff {int dummy; } ;
struct rfcomm_session {int /*<<< orphan*/  state; struct socket* sock; } ;

/* Variables and functions */
 scalar_t__ BT_CLOSED ; 
 int /*<<< orphan*/  BT_DBG (char*,struct rfcomm_session*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct rfcomm_session* rfcomm_recv_frame (struct rfcomm_session*,struct sk_buff*) ; 
 struct rfcomm_session* rfcomm_session_close (struct rfcomm_session*,int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_linearize (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_orphan (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_queue_len (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct rfcomm_session *rfcomm_process_rx(struct rfcomm_session *s)
{
	struct socket *sock = s->sock;
	struct sock *sk = sock->sk;
	struct sk_buff *skb;

	BT_DBG("session %p state %ld qlen %d", s, s->state, skb_queue_len(&sk->sk_receive_queue));

	/* Get data directly from socket receive queue without copying it. */
	while ((skb = skb_dequeue(&sk->sk_receive_queue))) {
		skb_orphan(skb);
		if (!skb_linearize(skb)) {
			s = rfcomm_recv_frame(s, skb);
			if (!s)
				break;
		} else {
			kfree_skb(skb);
		}
	}

	if (s && (sk->sk_state == BT_CLOSED))
		s = rfcomm_session_close(s, sk->sk_err);

	return s;
}