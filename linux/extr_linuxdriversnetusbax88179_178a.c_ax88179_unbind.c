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
typedef  scalar_t__ u16 ;
struct usbnet {int dummy; } ;
struct usb_interface {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AX_ACCESS_MAC ; 
 int /*<<< orphan*/  AX_CLK_SELECT ; 
 int /*<<< orphan*/  AX_PHYPWR_RSTCTL ; 
 int /*<<< orphan*/  AX_RX_CTL ; 
 scalar_t__ AX_RX_CTL_STOP ; 
 int /*<<< orphan*/  ax88179_write_cmd (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,scalar_t__*) ; 

__attribute__((used)) static void ax88179_unbind(struct usbnet *dev, struct usb_interface *intf)
{
	u16 tmp16;

	/* Configure RX control register => stop operation */
	tmp16 = AX_RX_CTL_STOP;
	ax88179_write_cmd(dev, AX_ACCESS_MAC, AX_RX_CTL, 2, 2, &tmp16);

	tmp16 = 0;
	ax88179_write_cmd(dev, AX_ACCESS_MAC, AX_CLK_SELECT, 1, 1, &tmp16);

	/* Power down ethernet PHY */
	tmp16 = 0;
	ax88179_write_cmd(dev, AX_ACCESS_MAC, AX_PHYPWR_RSTCTL, 2, 2, &tmp16);
}