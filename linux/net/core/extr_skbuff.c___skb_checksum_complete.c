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
struct sk_buff {scalar_t__ ip_summed; int csum_complete_sw; int csum_valid; int /*<<< orphan*/  csum; int /*<<< orphan*/  dev; int /*<<< orphan*/  len; } ;
typedef  int /*<<< orphan*/  __wsum ;
typedef  int /*<<< orphan*/  __sum16 ;

/* Variables and functions */
 scalar_t__ CHECKSUM_COMPLETE ; 
 int /*<<< orphan*/  csum_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csum_fold (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  netdev_rx_csum_fault (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_checksum (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_shared (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__sum16 __skb_checksum_complete(struct sk_buff *skb)
{
	__wsum csum;
	__sum16 sum;

	csum = skb_checksum(skb, 0, skb->len, 0);

	sum = csum_fold(csum_add(skb->csum, csum));
	/* This check is inverted, because we already knew the hardware
	 * checksum is invalid before calling this function. So, if the
	 * re-computed checksum is valid instead, then we have a mismatch
	 * between the original skb->csum and skb_checksum(). This means either
	 * the original hardware checksum is incorrect or we screw up skb->csum
	 * when moving skb->data around.
	 */
	if (likely(!sum)) {
		if (unlikely(skb->ip_summed == CHECKSUM_COMPLETE) &&
		    !skb->csum_complete_sw)
			netdev_rx_csum_fault(skb->dev, skb);
	}

	if (!skb_shared(skb)) {
		/* Save full packet checksum */
		skb->csum = csum;
		skb->ip_summed = CHECKSUM_COMPLETE;
		skb->csum_complete_sw = 1;
		skb->csum_valid = !sum;
	}

	return sum;
}