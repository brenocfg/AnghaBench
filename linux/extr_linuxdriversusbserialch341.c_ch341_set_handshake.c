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
struct usb_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CH341_REQ_MODEM_CTRL ; 
 int ch341_control_out (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ch341_set_handshake(struct usb_device *dev, u8 control)
{
	return ch341_control_out(dev, CH341_REQ_MODEM_CTRL, ~control, 0);
}