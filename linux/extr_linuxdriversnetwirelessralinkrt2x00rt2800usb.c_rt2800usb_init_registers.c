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
typedef  int u32 ;
struct rt2x00_dev {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  MAC_SYS_CTRL ; 
 int /*<<< orphan*/  MAC_SYS_CTRL_RESET_BBP ; 
 int /*<<< orphan*/  MAC_SYS_CTRL_RESET_CSR ; 
 int /*<<< orphan*/  PBF_SYS_CTRL ; 
 int /*<<< orphan*/  REGISTER_TIMEOUT ; 
 int /*<<< orphan*/  USB_DEVICE_MODE ; 
 int /*<<< orphan*/  USB_MODE_RESET ; 
 scalar_t__ rt2800_wait_csr_ready (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2x00_set_field32 (int*,int /*<<< orphan*/ ,int) ; 
 int rt2x00usb_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00usb_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt2x00usb_vendor_request_sw (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rt2800usb_init_registers(struct rt2x00_dev *rt2x00dev)
{
	u32 reg;

	/*
	 * Wait until BBP and RF are ready.
	 */
	if (rt2800_wait_csr_ready(rt2x00dev))
		return -EBUSY;

	reg = rt2x00usb_register_read(rt2x00dev, PBF_SYS_CTRL);
	rt2x00usb_register_write(rt2x00dev, PBF_SYS_CTRL, reg & ~0x00002000);

	reg = 0;
	rt2x00_set_field32(&reg, MAC_SYS_CTRL_RESET_CSR, 1);
	rt2x00_set_field32(&reg, MAC_SYS_CTRL_RESET_BBP, 1);
	rt2x00usb_register_write(rt2x00dev, MAC_SYS_CTRL, reg);

	rt2x00usb_vendor_request_sw(rt2x00dev, USB_DEVICE_MODE, 0,
				    USB_MODE_RESET, REGISTER_TIMEOUT);

	rt2x00usb_register_write(rt2x00dev, MAC_SYS_CTRL, 0x00000000);

	return 0;
}