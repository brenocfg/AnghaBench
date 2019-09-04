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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct net {int dummy; } ;
struct TYPE_4__ {scalar_t__ seq; scalar_t__ end_seq; } ;
struct TYPE_3__ {int /*<<< orphan*/  syn; } ;

/* Variables and functions */
 TYPE_2__* TCP_SKB_CB (struct sk_buff const*) ; 
 int __tcp_oow_rate_limited (struct net*,int,int /*<<< orphan*/ *) ; 
 TYPE_1__* tcp_hdr (struct sk_buff const*) ; 

bool tcp_oow_rate_limited(struct net *net, const struct sk_buff *skb,
			  int mib_idx, u32 *last_oow_ack_time)
{
	/* Data packets without SYNs are not likely part of an ACK loop. */
	if ((TCP_SKB_CB(skb)->seq != TCP_SKB_CB(skb)->end_seq) &&
	    !tcp_hdr(skb)->syn)
		return false;

	return __tcp_oow_rate_limited(net, mib_idx, last_oow_ack_time);
}