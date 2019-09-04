#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {scalar_t__ cb; } ;
struct TYPE_4__ {int msg_seq; int /*<<< orphan*/  mutex; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct mt76x2_dev {TYPE_2__ mcu; TYPE_1__ mt76; } ;
typedef  enum mcu_cmd { ____Placeholder_mcu_cmd } mcu_cmd ;

/* Variables and functions */
 int EINVAL ; 
 int ETIMEDOUT ; 
 scalar_t__ FIELD_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long HZ ; 
 int /*<<< orphan*/  MT_RX_FCE_INFO_CMD_SEQ ; 
 int /*<<< orphan*/  MT_TXQ_MCU ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,scalar_t__) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 unsigned long jiffies ; 
 struct sk_buff* mt76x2_mcu_get_response (struct mt76x2_dev*,unsigned long) ; 
 int mt76x2_tx_queue_mcu (struct mt76x2_dev*,int /*<<< orphan*/ ,struct sk_buff*,int,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mt76x2_mcu_msg_send(struct mt76x2_dev *dev, struct sk_buff *skb,
		    enum mcu_cmd cmd)
{
	unsigned long expires = jiffies + HZ;
	int ret;
	u8 seq;

	if (!skb)
		return -EINVAL;

	mutex_lock(&dev->mcu.mutex);

	seq = ++dev->mcu.msg_seq & 0xf;
	if (!seq)
		seq = ++dev->mcu.msg_seq & 0xf;

	ret = mt76x2_tx_queue_mcu(dev, MT_TXQ_MCU, skb, cmd, seq);
	if (ret)
		goto out;

	while (1) {
		u32 *rxfce;
		bool check_seq = false;

		skb = mt76x2_mcu_get_response(dev, expires);
		if (!skb) {
			dev_err(dev->mt76.dev,
				"MCU message %d (seq %d) timed out\n", cmd,
				seq);
			ret = -ETIMEDOUT;
			break;
		}

		rxfce = (u32 *) skb->cb;

		if (seq == FIELD_GET(MT_RX_FCE_INFO_CMD_SEQ, *rxfce))
			check_seq = true;

		dev_kfree_skb(skb);
		if (check_seq)
			break;
	}

out:
	mutex_unlock(&dev->mcu.mutex);

	return ret;
}