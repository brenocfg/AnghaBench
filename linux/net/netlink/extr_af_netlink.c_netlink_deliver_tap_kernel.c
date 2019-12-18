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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  netlink_deliver_tap (int /*<<< orphan*/ ,struct sk_buff*) ; 
 scalar_t__ netlink_is_kernel (struct sock*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 

__attribute__((used)) static void netlink_deliver_tap_kernel(struct sock *dst, struct sock *src,
				       struct sk_buff *skb)
{
	if (!(netlink_is_kernel(dst) && netlink_is_kernel(src)))
		netlink_deliver_tap(sock_net(dst), skb);
}