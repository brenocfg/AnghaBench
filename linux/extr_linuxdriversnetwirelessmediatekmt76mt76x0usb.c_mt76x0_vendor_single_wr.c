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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct mt76x0_dev {int /*<<< orphan*/  usb_ctrl_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_DIR_OUT ; 
 int mt76x0_vendor_request (struct mt76x0_dev*,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int const,scalar_t__ const,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int mt76x0_vendor_single_wr(struct mt76x0_dev *dev, const u8 req,
			     const u16 offset, const u32 val)
{
	struct mt76x0_dev *mdev = dev;
	int ret;

	mutex_lock(&mdev->usb_ctrl_mtx);

	ret = mt76x0_vendor_request(dev, req, USB_DIR_OUT,
				    val & 0xffff, offset, NULL, 0);
	if (!ret)
		ret = mt76x0_vendor_request(dev, req, USB_DIR_OUT,
					    val >> 16, offset + 2, NULL, 0);

	mutex_unlock(&mdev->usb_ctrl_mtx);

	return ret;
}