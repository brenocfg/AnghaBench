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
struct mt76x0_dev {int /*<<< orphan*/  usb_ctrl_mtx; int /*<<< orphan*/  data; } ;
struct mt76_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int MT_VEND_BUF ; 
 int /*<<< orphan*/  MT_VEND_MULTI_READ ; 
 int /*<<< orphan*/  USB_DIR_IN ; 
 int /*<<< orphan*/  USHRT_MAX ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_unaligned_le32 (int /*<<< orphan*/ ) ; 
 int mt76x0_vendor_request (struct mt76x0_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_mt76x0_reg_read (struct mt76_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 mt76x0_rr(struct mt76_dev *dev, u32 offset)
{
	struct mt76x0_dev *mdev = (struct mt76x0_dev *) dev;
	int ret;
	u32 val = ~0;

	WARN_ONCE(offset > USHRT_MAX, "read high off:%08x", offset);

	mutex_lock(&mdev->usb_ctrl_mtx);

	ret = mt76x0_vendor_request((struct mt76x0_dev *)dev, MT_VEND_MULTI_READ, USB_DIR_IN,
				    0, offset, mdev->data, MT_VEND_BUF);
	if (ret == MT_VEND_BUF)
		val = get_unaligned_le32(mdev->data);
	else if (ret > 0)
		dev_err(dev->dev, "Error: wrong size read:%d off:%08x\n",
			ret, offset);

	mutex_unlock(&mdev->usb_ctrl_mtx);

	trace_mt76x0_reg_read(dev, offset, val);
	return val;
}