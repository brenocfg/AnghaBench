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
struct kaweth_device {int /*<<< orphan*/  configuration; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  KAWETH_COMMAND_GET_ETHERNET_DESC ; 
 int /*<<< orphan*/  KAWETH_CONTROL_TIMEOUT ; 
 int USB_DIR_IN ; 
 int USB_RECIP_DEVICE ; 
 int USB_TYPE_VENDOR ; 
 int kaweth_control (struct kaweth_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kaweth_read_configuration(struct kaweth_device *kaweth)
{
	int retval;

	retval = kaweth_control(kaweth,
				usb_rcvctrlpipe(kaweth->dev, 0),
				KAWETH_COMMAND_GET_ETHERNET_DESC,
				USB_TYPE_VENDOR | USB_DIR_IN | USB_RECIP_DEVICE,
				0,
				0,
				(void *)&kaweth->configuration,
				sizeof(kaweth->configuration),
				KAWETH_CONTROL_TIMEOUT);

	return retval;
}