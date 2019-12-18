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
struct sk_buff {int dummy; } ;
struct inet6_skb_parm {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  h6; } ;
struct TYPE_4__ {TYPE_1__ header; } ;

/* Variables and functions */
 int /*<<< orphan*/  IP6CB (struct sk_buff*) ; 
 TYPE_2__* TCP_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void tcp_v6_restore_cb(struct sk_buff *skb)
{
	/* We need to move header back to the beginning if xfrm6_policy_check()
	 * and tcp_v6_fill_cb() are going to be called again.
	 * ip6_datagram_recv_specific_ctl() also expects IP6CB to be there.
	 */
	memmove(IP6CB(skb), &TCP_SKB_CB(skb)->header.h6,
		sizeof(struct inet6_skb_parm));
}