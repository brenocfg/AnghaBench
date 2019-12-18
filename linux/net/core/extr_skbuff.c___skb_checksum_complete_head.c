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
struct sk_buff {scalar_t__ ip_summed; int csum_valid; int /*<<< orphan*/  dev; int /*<<< orphan*/  csum_complete_sw; int /*<<< orphan*/  csum; } ;
typedef  int /*<<< orphan*/  __sum16 ;

/* Variables and functions */
 scalar_t__ CHECKSUM_COMPLETE ; 
 int /*<<< orphan*/  csum_fold (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  netdev_rx_csum_fault (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_checksum (struct sk_buff*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_shared (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__sum16 __skb_checksum_complete_head(struct sk_buff *skb, int len)
{
	__sum16 sum;

	sum = csum_fold(skb_checksum(skb, 0, len, skb->csum));
	/* See comments in __skb_checksum_complete(). */
	if (likely(!sum)) {
		if (unlikely(skb->ip_summed == CHECKSUM_COMPLETE) &&
		    !skb->csum_complete_sw)
			netdev_rx_csum_fault(skb->dev, skb);
	}
	if (!skb_shared(skb))
		skb->csum_valid = !sum;
	return sum;
}