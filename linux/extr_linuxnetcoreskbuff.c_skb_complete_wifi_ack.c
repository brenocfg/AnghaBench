#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  ee_origin; int /*<<< orphan*/  ee_errno; } ;
struct sock_exterr_skb {TYPE_1__ ee; } ;
struct sock {int /*<<< orphan*/  sk_refcnt; } ;
struct sk_buff {int wifi_acked_valid; int wifi_acked; struct sock* sk; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMSG ; 
 struct sock_exterr_skb* SKB_EXT_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  SO_EE_ORIGIN_TXSTATUS ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct sock_exterr_skb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  refcount_inc_not_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 int sock_queue_err_skb (struct sock*,struct sk_buff*) ; 

void skb_complete_wifi_ack(struct sk_buff *skb, bool acked)
{
	struct sock *sk = skb->sk;
	struct sock_exterr_skb *serr;
	int err = 1;

	skb->wifi_acked_valid = 1;
	skb->wifi_acked = acked;

	serr = SKB_EXT_ERR(skb);
	memset(serr, 0, sizeof(*serr));
	serr->ee.ee_errno = ENOMSG;
	serr->ee.ee_origin = SO_EE_ORIGIN_TXSTATUS;

	/* Take a reference to prevent skb_orphan() from freeing the socket,
	 * but only if the socket refcount is not zero.
	 */
	if (likely(refcount_inc_not_zero(&sk->sk_refcnt))) {
		err = sock_queue_err_skb(sk, skb);
		sock_put(sk);
	}
	if (err)
		kfree_skb(skb);
}