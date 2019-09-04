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
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int _tsize_state; } ;

/* Variables and functions */
 int UDP_SKB_IS_STATELESS ; 
 TYPE_1__* udp_skb_scratch (struct sk_buff*) ; 

__attribute__((used)) static bool udp_skb_has_head_state(struct sk_buff *skb)
{
	return !(udp_skb_scratch(skb)->_tsize_state & UDP_SKB_IS_STATELESS);
}