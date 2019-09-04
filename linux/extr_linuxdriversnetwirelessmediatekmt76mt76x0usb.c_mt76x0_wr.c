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
struct mt76x0_dev {int /*<<< orphan*/  usb_ctrl_mtx; int /*<<< orphan*/  data; } ;
struct mt76_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_VEND_BUF ; 
 int /*<<< orphan*/  MT_VEND_MULTI_WRITE ; 
 int /*<<< orphan*/  USB_DIR_OUT ; 
 scalar_t__ USHRT_MAX ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,scalar_t__) ; 
 int mt76x0_vendor_request (struct mt76x0_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_unaligned_le32 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_mt76x0_reg_write (struct mt76_dev*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void mt76x0_wr(struct mt76_dev *dev, u32 offset, u32 val)
{
	struct mt76x0_dev *mdev = (struct mt76x0_dev *) dev;
	int ret;

	WARN_ONCE(offset > USHRT_MAX, "write high off:%08x", offset);

	mutex_lock(&mdev->usb_ctrl_mtx);

	put_unaligned_le32(val, mdev->data);
	ret = mt76x0_vendor_request(mdev, MT_VEND_MULTI_WRITE, USB_DIR_OUT,
				    0, offset, mdev->data, MT_VEND_BUF);
	trace_mt76x0_reg_write(dev, offset, val);

	mutex_unlock(&mdev->usb_ctrl_mtx);
}