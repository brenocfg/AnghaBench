#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct udp_sock {scalar_t__ pending; scalar_t__ len; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct flowi4 {int dummy; } ;
struct TYPE_4__ {struct flowi4 ip4; } ;
struct TYPE_5__ {TYPE_1__ u; } ;
struct TYPE_6__ {int /*<<< orphan*/  base; TYPE_2__ fl; } ;
struct inet_sock {TYPE_3__ cork; } ;

/* Variables and functions */
 struct inet_sock* inet_sk (struct sock*) ; 
 struct sk_buff* ip_finish_skb (struct sock*,struct flowi4*) ; 
 int udp_send_skb (struct sk_buff*,struct flowi4*,int /*<<< orphan*/ *) ; 
 struct udp_sock* udp_sk (struct sock*) ; 

int udp_push_pending_frames(struct sock *sk)
{
	struct udp_sock  *up = udp_sk(sk);
	struct inet_sock *inet = inet_sk(sk);
	struct flowi4 *fl4 = &inet->cork.fl.u.ip4;
	struct sk_buff *skb;
	int err = 0;

	skb = ip_finish_skb(sk, fl4);
	if (!skb)
		goto out;

	err = udp_send_skb(skb, fl4, &inet->cork.base);

out:
	up->len = 0;
	up->pending = 0;
	return err;
}