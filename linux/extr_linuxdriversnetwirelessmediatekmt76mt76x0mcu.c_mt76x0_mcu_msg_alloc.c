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
struct sk_buff {int dummy; } ;
struct mt76x0_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ MT_DMA_HDR_LEN ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct sk_buff* alloc_skb (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 

__attribute__((used)) static struct sk_buff *
mt76x0_mcu_msg_alloc(struct mt76x0_dev *dev, const void *data, int len)
{
	struct sk_buff *skb;

	WARN_ON(len % 4); /* if length is not divisible by 4 we need to pad */

	skb = alloc_skb(len + MT_DMA_HDR_LEN + 4, GFP_KERNEL);
	if (skb) {
		skb_reserve(skb, MT_DMA_HDR_LEN);
		memcpy(skb_put(skb, len), data, len);
	}
	return skb;
}