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
struct sk_buff {scalar_t__ ip_summed; unsigned int len; int /*<<< orphan*/  csum; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_COMPLETE ; 
 int __pskb_trim (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  csum_block_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  skb_checksum (struct sk_buff*,unsigned int,int,int /*<<< orphan*/ ) ; 

int pskb_trim_rcsum_slow(struct sk_buff *skb, unsigned int len)
{
	if (skb->ip_summed == CHECKSUM_COMPLETE) {
		int delta = skb->len - len;

		skb->csum = csum_block_sub(skb->csum,
					   skb_checksum(skb, len, delta, 0),
					   len);
	}
	return __pskb_trim(skb, len);
}