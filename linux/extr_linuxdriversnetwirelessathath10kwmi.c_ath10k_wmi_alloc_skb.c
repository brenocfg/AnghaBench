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
typedef  scalar_t__ u32 ;
struct sk_buff {scalar_t__ data; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ALIGNED (unsigned long,int) ; 
 scalar_t__ WMI_SKB_HEADROOM ; 
 struct sk_buff* ath10k_htc_alloc_skb (struct ath10k*,scalar_t__) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ roundup (scalar_t__,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 

struct sk_buff *ath10k_wmi_alloc_skb(struct ath10k *ar, u32 len)
{
	struct sk_buff *skb;
	u32 round_len = roundup(len, 4);

	skb = ath10k_htc_alloc_skb(ar, WMI_SKB_HEADROOM + round_len);
	if (!skb)
		return NULL;

	skb_reserve(skb, WMI_SKB_HEADROOM);
	if (!IS_ALIGNED((unsigned long)skb->data, 4))
		ath10k_warn(ar, "Unaligned WMI skb\n");

	skb_put(skb, round_len);
	memset(skb->data, 0, round_len);

	return skb;
}