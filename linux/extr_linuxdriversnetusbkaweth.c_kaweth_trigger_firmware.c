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
struct kaweth_device {int* firmware_buf; int /*<<< orphan*/  dev; } ;
typedef  int __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  KAWETH_COMMAND_SCAN ; 
 int /*<<< orphan*/  KAWETH_CONTROL_TIMEOUT ; 
 int USB_DIR_OUT ; 
 int USB_RECIP_DEVICE ; 
 int USB_TYPE_VENDOR ; 
 int kaweth_control (struct kaweth_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kaweth_trigger_firmware(struct kaweth_device *kaweth,
				   __u8 interrupt)
{
	kaweth->firmware_buf[0] = 0xB6;
	kaweth->firmware_buf[1] = 0xC3;
	kaweth->firmware_buf[2] = 0x01;
	kaweth->firmware_buf[3] = 0x00;
	kaweth->firmware_buf[4] = 0x06;
	kaweth->firmware_buf[5] = interrupt;
	kaweth->firmware_buf[6] = 0x00;
	kaweth->firmware_buf[7] = 0x00;

	return kaweth_control(kaweth,
			      usb_sndctrlpipe(kaweth->dev, 0),
			      KAWETH_COMMAND_SCAN,
			      USB_TYPE_VENDOR | USB_DIR_OUT | USB_RECIP_DEVICE,
			      0,
			      0,
			      (void *)kaweth->firmware_buf,
			      8,
			      KAWETH_CONTROL_TIMEOUT);
}