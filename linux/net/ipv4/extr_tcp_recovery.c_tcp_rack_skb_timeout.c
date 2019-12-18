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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ rtt_us; } ;
struct tcp_sock {int /*<<< orphan*/  tcp_mstamp; TYPE_1__ rack; } ;
struct sk_buff {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  tcp_skb_timestamp_us (struct sk_buff*) ; 
 scalar_t__ tcp_stamp_us_delta (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

s32 tcp_rack_skb_timeout(struct tcp_sock *tp, struct sk_buff *skb, u32 reo_wnd)
{
	return tp->rack.rtt_us + reo_wnd -
	       tcp_stamp_us_delta(tp->tcp_mstamp, tcp_skb_timestamp_us(skb));
}