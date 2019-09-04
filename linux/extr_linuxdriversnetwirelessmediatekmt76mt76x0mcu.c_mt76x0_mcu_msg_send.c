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
struct sk_buff {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  mutex; } ;
struct TYPE_3__ {int /*<<< orphan*/  state; } ;
struct mt76x0_dev {TYPE_2__ mcu; TYPE_1__ mt76; } ;
typedef  enum mcu_cmd { ____Placeholder_mcu_cmd } mcu_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  MT76_REMOVED ; 
 int __mt76x0_mcu_msg_send (struct mt76x0_dev*,struct sk_buff*,int,int) ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mt76x0_mcu_msg_send(struct mt76x0_dev *dev, struct sk_buff *skb,
		     enum mcu_cmd cmd, bool wait_resp)
{
	int ret;

	if (test_bit(MT76_REMOVED, &dev->mt76.state))
		return 0;

	mutex_lock(&dev->mcu.mutex);
	ret = __mt76x0_mcu_msg_send(dev, skb, cmd, wait_resp);
	mutex_unlock(&dev->mcu.mutex);

	consume_skb(skb);

	return ret;
}