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
struct sk_buff {TYPE_1__* dev; } ;
struct TYPE_2__ {scalar_t__ hard_header_len; scalar_t__ mtu; } ;

/* Variables and functions */
 scalar_t__ SKB_MAX_ALLOC ; 

__attribute__((used)) static u32 __bpf_skb_max_len(const struct sk_buff *skb)
{
	return skb->dev ? skb->dev->mtu + skb->dev->hard_header_len :
			  SKB_MAX_ALLOC;
}