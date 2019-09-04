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
struct sock {int /*<<< orphan*/  sk_write_queue; } ;
struct sk_buff {int dummy; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int ip6_push_pending_frames (struct sock*) ; 
 struct sk_buff* skb_peek (int /*<<< orphan*/ *) ; 
 scalar_t__ skb_transport_header (struct sk_buff*) ; 

__attribute__((used)) static int l2tp_ip6_push_pending_frames(struct sock *sk)
{
	struct sk_buff *skb;
	__be32 *transhdr = NULL;
	int err = 0;

	skb = skb_peek(&sk->sk_write_queue);
	if (skb == NULL)
		goto out;

	transhdr = (__be32 *)skb_transport_header(skb);
	*transhdr = 0;

	err = ip6_push_pending_frames(sk);

out:
	return err;
}