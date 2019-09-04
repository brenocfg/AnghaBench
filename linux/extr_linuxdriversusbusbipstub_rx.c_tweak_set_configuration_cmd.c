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
struct usb_ctrlrequest {int /*<<< orphan*/  wValue; } ;
struct urb {scalar_t__ setup_packet; scalar_t__ context; } ;
struct stub_priv {struct stub_device* sdev; } ;
struct stub_device {TYPE_1__* udev; } ;
typedef  int /*<<< orphan*/  __u16 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int usb_set_configuration (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tweak_set_configuration_cmd(struct urb *urb)
{
	struct stub_priv *priv = (struct stub_priv *) urb->context;
	struct stub_device *sdev = priv->sdev;
	struct usb_ctrlrequest *req;
	__u16 config;
	int err;

	req = (struct usb_ctrlrequest *) urb->setup_packet;
	config = le16_to_cpu(req->wValue);

	err = usb_set_configuration(sdev->udev, config);
	if (err && err != -ENODEV)
		dev_err(&sdev->udev->dev, "can't set config #%d, error %d\n",
			config, err);
	return 0;
}