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
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int reg_pairs_len; int burst_read; int /*<<< orphan*/  mutex; struct mt76_reg_pair* reg_pairs; scalar_t__ reg_base; } ;
struct mt76x0_dev {TYPE_1__ mcu; } ;
struct mt76_reg_pair {scalar_t__ value; scalar_t__ reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_RANDOM_READ ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int INBAND_PACKET_MAX_LEN ; 
 scalar_t__ MT_DMA_HDR_LEN ; 
 int __mt76x0_mcu_msg_send (struct mt76x0_dev*,struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 struct sk_buff* alloc_skb (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 int min (int const,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_put_le32 (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 

int mt76x0_read_reg_pairs(struct mt76x0_dev *dev, u32 base,
			  struct mt76_reg_pair *data, int n)
{
	const int max_vals_per_cmd = INBAND_PACKET_MAX_LEN / 8;
	struct sk_buff *skb;
	int cnt, i, ret;

	if (!n)
		return 0;

	cnt = min(max_vals_per_cmd, n);
	if (cnt != n)
		return -EINVAL;

	skb = alloc_skb(cnt * 8 + MT_DMA_HDR_LEN + 4, GFP_KERNEL);
	if (!skb)
		return -ENOMEM;
	skb_reserve(skb, MT_DMA_HDR_LEN);

	for (i = 0; i < cnt; i++) {
		skb_put_le32(skb, base + data[i].reg);
		skb_put_le32(skb, data[i].value);
	}

	mutex_lock(&dev->mcu.mutex);

	dev->mcu.reg_pairs = data;
	dev->mcu.reg_pairs_len = n;
	dev->mcu.reg_base = base;
	dev->mcu.burst_read = false;

	ret = __mt76x0_mcu_msg_send(dev, skb, CMD_RANDOM_READ, true);

	dev->mcu.reg_pairs = NULL;

	mutex_unlock(&dev->mcu.mutex);

	consume_skb(skb);

	return ret;

}