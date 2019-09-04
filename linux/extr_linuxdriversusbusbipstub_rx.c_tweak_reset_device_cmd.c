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
struct urb {TYPE_1__* dev; scalar_t__ context; } ;
struct stub_priv {struct stub_device* sdev; } ;
struct stub_device {int /*<<< orphan*/  udev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ usb_lock_device_for_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_reset_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_unlock_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tweak_reset_device_cmd(struct urb *urb)
{
	struct stub_priv *priv = (struct stub_priv *) urb->context;
	struct stub_device *sdev = priv->sdev;

	dev_info(&urb->dev->dev, "usb_queue_reset_device\n");

	if (usb_lock_device_for_reset(sdev->udev, NULL) < 0) {
		dev_err(&urb->dev->dev, "could not obtain lock to reset device\n");
		return 0;
	}
	usb_reset_device(sdev->udev);
	usb_unlock_device(sdev->udev);

	return 0;
}