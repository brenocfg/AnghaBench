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
struct ab8500_usb {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AB8500_BANK12_ACCESS ; 
 int /*<<< orphan*/  AB8500_DEBUG ; 
 int /*<<< orphan*/  AB8500_DEVELOPMENT ; 
 int /*<<< orphan*/  AB8500_USB_PHY_TUNE1 ; 
 int /*<<< orphan*/  AB8500_USB_PHY_TUNE2 ; 
 int /*<<< orphan*/  AB8500_USB_PHY_TUNE3 ; 
 int abx500_set_register_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void ab8500_usb_set_ab8500_tuning_values(struct ab8500_usb *ab)
{
	int err;

	/* Enable the PBT/Bank 0x12 access */
	err = abx500_set_register_interruptible(ab->dev,
			AB8500_DEVELOPMENT, AB8500_BANK12_ACCESS, 0x01);
	if (err < 0)
		dev_err(ab->dev, "Failed to enable bank12 access err=%d\n",
				err);

	err = abx500_set_register_interruptible(ab->dev,
			AB8500_DEBUG, AB8500_USB_PHY_TUNE1, 0xC8);
	if (err < 0)
		dev_err(ab->dev, "Failed to set PHY_TUNE1 register err=%d\n",
				err);

	err = abx500_set_register_interruptible(ab->dev,
			AB8500_DEBUG, AB8500_USB_PHY_TUNE2, 0x00);
	if (err < 0)
		dev_err(ab->dev, "Failed to set PHY_TUNE2 register err=%d\n",
				err);

	err = abx500_set_register_interruptible(ab->dev,
			AB8500_DEBUG, AB8500_USB_PHY_TUNE3, 0x78);
	if (err < 0)
		dev_err(ab->dev, "Failed to set PHY_TUNE3 register err=%d\n",
				err);

	/* Switch to normal mode/disable Bank 0x12 access */
	err = abx500_set_register_interruptible(ab->dev,
			AB8500_DEVELOPMENT, AB8500_BANK12_ACCESS, 0x00);
	if (err < 0)
		dev_err(ab->dev, "Failed to switch bank12 access err=%d\n",
				err);
}