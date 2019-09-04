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
struct sk_buff {int len; int /*<<< orphan*/  data; } ;
struct s3fwrn5_i2c_phy {int irq_skip; int /*<<< orphan*/  mutex; int /*<<< orphan*/  i2c_dev; } ;

/* Variables and functions */
 int EREMOTEIO ; 
 int i2c_master_send (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int s3fwrn5_i2c_write(void *phy_id, struct sk_buff *skb)
{
	struct s3fwrn5_i2c_phy *phy = phy_id;
	int ret;

	mutex_lock(&phy->mutex);

	phy->irq_skip = false;

	ret = i2c_master_send(phy->i2c_dev, skb->data, skb->len);
	if (ret == -EREMOTEIO) {
		/* Retry, chip was in standby */
		usleep_range(110000, 120000);
		ret  = i2c_master_send(phy->i2c_dev, skb->data, skb->len);
	}

	mutex_unlock(&phy->mutex);

	if (ret < 0)
		return ret;

	if (ret != skb->len)
		return -EREMOTEIO;

	return 0;
}