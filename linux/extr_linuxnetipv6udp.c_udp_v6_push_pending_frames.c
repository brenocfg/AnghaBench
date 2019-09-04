#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct udp_sock {scalar_t__ pending; scalar_t__ len; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct flowi6 {int dummy; } ;
struct TYPE_5__ {struct flowi6 ip6; } ;
struct TYPE_6__ {TYPE_1__ u; } ;
struct TYPE_7__ {int /*<<< orphan*/  base; TYPE_2__ fl; } ;
struct TYPE_8__ {TYPE_3__ cork; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 TYPE_4__* inet_sk (struct sock*) ; 
 struct sk_buff* ip6_finish_skb (struct sock*) ; 
 int udp_push_pending_frames (struct sock*) ; 
 struct udp_sock* udp_sk (struct sock*) ; 
 int udp_v6_send_skb (struct sk_buff*,struct flowi6*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int udp_v6_push_pending_frames(struct sock *sk)
{
	struct sk_buff *skb;
	struct udp_sock  *up = udp_sk(sk);
	struct flowi6 fl6;
	int err = 0;

	if (up->pending == AF_INET)
		return udp_push_pending_frames(sk);

	/* ip6_finish_skb will release the cork, so make a copy of
	 * fl6 here.
	 */
	fl6 = inet_sk(sk)->cork.fl.u.ip6;

	skb = ip6_finish_skb(sk);
	if (!skb)
		goto out;

	err = udp_v6_send_skb(skb, &fl6, &inet_sk(sk)->cork.base);

out:
	up->len = 0;
	up->pending = 0;
	return err;
}