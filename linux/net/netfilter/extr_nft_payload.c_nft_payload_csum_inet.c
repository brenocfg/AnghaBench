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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  sum ;
struct sk_buff {int dummy; } ;
typedef  int /*<<< orphan*/  __wsum ;
typedef  int /*<<< orphan*/  __sum16 ;

/* Variables and functions */
 int /*<<< orphan*/  nft_csum_replace (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_copy_bits (struct sk_buff*,int,int /*<<< orphan*/ *,int) ; 
 scalar_t__ skb_ensure_writable (struct sk_buff*,int) ; 
 scalar_t__ skb_store_bits (struct sk_buff*,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int nft_payload_csum_inet(struct sk_buff *skb, const u32 *src,
				 __wsum fsum, __wsum tsum, int csum_offset)
{
	__sum16 sum;

	if (skb_copy_bits(skb, csum_offset, &sum, sizeof(sum)) < 0)
		return -1;

	nft_csum_replace(&sum, fsum, tsum);
	if (skb_ensure_writable(skb, csum_offset + sizeof(sum)) ||
	    skb_store_bits(skb, csum_offset, &sum, sizeof(sum)) < 0)
		return -1;

	return 0;
}