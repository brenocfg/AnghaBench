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
struct sk_buff {scalar_t__ ip_summed; int /*<<< orphan*/  dev; int /*<<< orphan*/  csum_complete_sw; } ;
typedef  int /*<<< orphan*/  __wsum ;
typedef  int /*<<< orphan*/  __sum16 ;
struct TYPE_2__ {int csum_valid; int /*<<< orphan*/  csum; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_COMPLETE ; 
 TYPE_1__* NAPI_GRO_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  csum_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csum_fold (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  netdev_rx_csum_fault (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_checksum (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_gro_len (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_gro_offset (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__sum16 __skb_gro_checksum_complete(struct sk_buff *skb)
{
	__wsum wsum;
	__sum16 sum;

	wsum = skb_checksum(skb, skb_gro_offset(skb), skb_gro_len(skb), 0);

	/* NAPI_GRO_CB(skb)->csum holds pseudo checksum */
	sum = csum_fold(csum_add(NAPI_GRO_CB(skb)->csum, wsum));
	/* See comments in __skb_checksum_complete(). */
	if (likely(!sum)) {
		if (unlikely(skb->ip_summed == CHECKSUM_COMPLETE) &&
		    !skb->csum_complete_sw)
			netdev_rx_csum_fault(skb->dev, skb);
	}

	NAPI_GRO_CB(skb)->csum = wsum;
	NAPI_GRO_CB(skb)->csum_valid = 1;

	return sum;
}