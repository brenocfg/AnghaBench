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
struct usbnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM_WRITE_REG ; 
 int USB_DIR_OUT ; 
 int USB_RECIP_DEVICE ; 
 int USB_TYPE_VENDOR ; 
 int usbnet_write_cmd (struct usbnet*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dm_write_reg(struct usbnet *dev, u8 reg, u8 value)
{
	return usbnet_write_cmd(dev, DM_WRITE_REG,
				USB_DIR_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
				value, reg, NULL, 0);
}