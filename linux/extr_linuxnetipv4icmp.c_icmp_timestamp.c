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
struct sk_buff {int len; } ;
struct icmphdr {int dummy; } ;
struct TYPE_6__ {scalar_t__ code; int /*<<< orphan*/  type; } ;
struct TYPE_4__ {TYPE_3__ icmph; int /*<<< orphan*/ * times; } ;
struct icmp_bxm {int head_len; scalar_t__ data_len; scalar_t__ offset; struct sk_buff* skb; TYPE_1__ data; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ICMP_MIB_INERRORS ; 
 int /*<<< orphan*/  ICMP_TIMESTAMPREPLY ; 
 int /*<<< orphan*/  __ICMP_INC_STATS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_net (int /*<<< orphan*/ ) ; 
 TYPE_3__* icmp_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  icmp_reply (struct icmp_bxm*,struct sk_buff*) ; 
 int /*<<< orphan*/  inet_current_timestamp () ; 
 int /*<<< orphan*/  skb_copy_bits (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 TYPE_2__* skb_dst (struct sk_buff*) ; 

__attribute__((used)) static bool icmp_timestamp(struct sk_buff *skb)
{
	struct icmp_bxm icmp_param;
	/*
	 *	Too short.
	 */
	if (skb->len < 4)
		goto out_err;

	/*
	 *	Fill in the current time as ms since midnight UT:
	 */
	icmp_param.data.times[1] = inet_current_timestamp();
	icmp_param.data.times[2] = icmp_param.data.times[1];

	BUG_ON(skb_copy_bits(skb, 0, &icmp_param.data.times[0], 4));

	icmp_param.data.icmph	   = *icmp_hdr(skb);
	icmp_param.data.icmph.type = ICMP_TIMESTAMPREPLY;
	icmp_param.data.icmph.code = 0;
	icmp_param.skb		   = skb;
	icmp_param.offset	   = 0;
	icmp_param.data_len	   = 0;
	icmp_param.head_len	   = sizeof(struct icmphdr) + 12;
	icmp_reply(&icmp_param, skb);
	return true;

out_err:
	__ICMP_INC_STATS(dev_net(skb_dst(skb)->dev), ICMP_MIB_INERRORS);
	return false;
}