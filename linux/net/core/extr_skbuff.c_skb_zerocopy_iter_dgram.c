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
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct msghdr {int /*<<< orphan*/  msg_iter; } ;

/* Variables and functions */
 int __zerocopy_sg_from_iter (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ *,int) ; 

int skb_zerocopy_iter_dgram(struct sk_buff *skb, struct msghdr *msg, int len)
{
	return __zerocopy_sg_from_iter(skb->sk, skb, &msg->msg_iter, len);
}