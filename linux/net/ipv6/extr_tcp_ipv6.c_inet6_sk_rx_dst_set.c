#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sock {struct dst_entry* sk_rx_dst; } ;
struct sk_buff {int /*<<< orphan*/  skb_iif; } ;
struct rt6_info {int dummy; } ;
struct dst_entry {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  rx_dst_ifindex; } ;
struct TYPE_3__ {int /*<<< orphan*/  rx_dst_cookie; } ;

/* Variables and functions */
 scalar_t__ dst_hold_safe (struct dst_entry*) ; 
 TYPE_2__* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  rt6_get_cookie (struct rt6_info const*) ; 
 struct dst_entry* skb_dst (struct sk_buff const*) ; 
 TYPE_1__* tcp_inet6_sk (struct sock*) ; 

__attribute__((used)) static void inet6_sk_rx_dst_set(struct sock *sk, const struct sk_buff *skb)
{
	struct dst_entry *dst = skb_dst(skb);

	if (dst && dst_hold_safe(dst)) {
		const struct rt6_info *rt = (const struct rt6_info *)dst;

		sk->sk_rx_dst = dst;
		inet_sk(sk)->rx_dst_ifindex = skb->skb_iif;
		tcp_inet6_sk(sk)->rx_dst_cookie = rt6_get_cookie(rt);
	}
}