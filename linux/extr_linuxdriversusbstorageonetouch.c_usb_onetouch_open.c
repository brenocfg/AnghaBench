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
struct usb_onetouch {int is_open; TYPE_1__* irq; int /*<<< orphan*/  udev; } ;
struct input_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct usb_onetouch* input_get_drvdata (struct input_dev*) ; 
 scalar_t__ usb_submit_urb (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usb_onetouch_open(struct input_dev *dev)
{
	struct usb_onetouch *onetouch = input_get_drvdata(dev);

	onetouch->is_open = 1;
	onetouch->irq->dev = onetouch->udev;
	if (usb_submit_urb(onetouch->irq, GFP_KERNEL)) {
		dev_err(&dev->dev, "usb_submit_urb failed\n");
		return -EIO;
	}

	return 0;
}