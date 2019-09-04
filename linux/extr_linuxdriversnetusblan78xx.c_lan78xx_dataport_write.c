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
typedef  int u32 ;
struct lan78xx_priv {int /*<<< orphan*/  dataport_mutex; } ;
struct lan78xx_net {int /*<<< orphan*/  intf; scalar_t__* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ADDR ; 
 int /*<<< orphan*/  DP_CMD ; 
 int DP_CMD_WRITE_ ; 
 int /*<<< orphan*/  DP_DATA ; 
 int /*<<< orphan*/  DP_SEL ; 
 int DP_SEL_RSEL_MASK_ ; 
 int lan78xx_dataport_wait_not_busy (struct lan78xx_net*) ; 
 int lan78xx_read_reg (struct lan78xx_net*,int /*<<< orphan*/ ,int*) ; 
 int lan78xx_write_reg (struct lan78xx_net*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ usb_autopm_get_interface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lan78xx_dataport_write(struct lan78xx_net *dev, u32 ram_select,
				  u32 addr, u32 length, u32 *buf)
{
	struct lan78xx_priv *pdata = (struct lan78xx_priv *)(dev->data[0]);
	u32 dp_sel;
	int i, ret;

	if (usb_autopm_get_interface(dev->intf) < 0)
			return 0;

	mutex_lock(&pdata->dataport_mutex);

	ret = lan78xx_dataport_wait_not_busy(dev);
	if (ret < 0)
		goto done;

	ret = lan78xx_read_reg(dev, DP_SEL, &dp_sel);

	dp_sel &= ~DP_SEL_RSEL_MASK_;
	dp_sel |= ram_select;
	ret = lan78xx_write_reg(dev, DP_SEL, dp_sel);

	for (i = 0; i < length; i++) {
		ret = lan78xx_write_reg(dev, DP_ADDR, addr + i);

		ret = lan78xx_write_reg(dev, DP_DATA, buf[i]);

		ret = lan78xx_write_reg(dev, DP_CMD, DP_CMD_WRITE_);

		ret = lan78xx_dataport_wait_not_busy(dev);
		if (ret < 0)
			goto done;
	}

done:
	mutex_unlock(&pdata->dataport_mutex);
	usb_autopm_put_interface(dev->intf);

	return ret;
}