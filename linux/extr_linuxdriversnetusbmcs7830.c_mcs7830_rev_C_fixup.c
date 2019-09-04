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
typedef  int /*<<< orphan*/  u8 ;
struct usbnet {TYPE_1__* udev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HIF_REG_PAUSE_THRESHOLD ; 
 int /*<<< orphan*/  HIF_REG_PAUSE_THRESHOLD_DEFAULT ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int mcs7830_get_rev (struct usbnet*) ; 
 int /*<<< orphan*/  mcs7830_set_reg (struct usbnet*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void mcs7830_rev_C_fixup(struct usbnet *dev)
{
	u8 pause_threshold = HIF_REG_PAUSE_THRESHOLD_DEFAULT;
	int retry;

	for (retry = 0; retry < 2; retry++) {
		if (mcs7830_get_rev(dev) == 2) {
			dev_info(&dev->udev->dev, "applying rev.C fixup\n");
			mcs7830_set_reg(dev, HIF_REG_PAUSE_THRESHOLD,
					1, &pause_threshold);
		}
		msleep(1);
	}
}