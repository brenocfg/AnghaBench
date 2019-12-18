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
struct sk_buff {int /*<<< orphan*/ * sk; } ;
struct j1939_sock {int /*<<< orphan*/  sk; } ;
struct j1939_sk_buff_cb {int /*<<< orphan*/  msg_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  MSG_DONTROUTE ; 
 int /*<<< orphan*/  can_skb_set_owner (struct sk_buff*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  j1939_sk_recv_match_one (struct j1939_sock*,struct j1939_sk_buff_cb const*) ; 
 void* j1939_skb_to_cb (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ sock_queue_rcv_skb (int /*<<< orphan*/ *,struct sk_buff*) ; 

__attribute__((used)) static void j1939_sk_recv_one(struct j1939_sock *jsk, struct sk_buff *oskb)
{
	const struct j1939_sk_buff_cb *oskcb = j1939_skb_to_cb(oskb);
	struct j1939_sk_buff_cb *skcb;
	struct sk_buff *skb;

	if (oskb->sk == &jsk->sk)
		return;

	if (!j1939_sk_recv_match_one(jsk, oskcb))
		return;

	skb = skb_clone(oskb, GFP_ATOMIC);
	if (!skb) {
		pr_warn("skb clone failed\n");
		return;
	}
	can_skb_set_owner(skb, oskb->sk);

	skcb = j1939_skb_to_cb(skb);
	skcb->msg_flags &= ~(MSG_DONTROUTE);
	if (skb->sk)
		skcb->msg_flags |= MSG_DONTROUTE;

	if (sock_queue_rcv_skb(&jsk->sk, skb) < 0)
		kfree_skb(skb);
}