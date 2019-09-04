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
typedef  int u8 ;
typedef  int u32 ;
struct adapter {int dummy; } ;

/* Variables and functions */
 scalar_t__ REG_MCUFWDL ; 
 int /*<<< orphan*/  _rtl88e_fw_block_write (struct adapter*,int const*,int) ; 
 int usb_read8 (struct adapter*,scalar_t__) ; 
 int /*<<< orphan*/  usb_write8 (struct adapter*,scalar_t__,int) ; 

__attribute__((used)) static void _rtl88e_fw_page_write(struct adapter *adapt,
				  u32 page, const u8 *buffer, u32 size)
{
	u8 value8;
	u8 u8page = (u8)(page & 0x07);

	value8 = (usb_read8(adapt, REG_MCUFWDL + 2) & 0xF8) | u8page;

	usb_write8(adapt, (REG_MCUFWDL + 2), value8);
	_rtl88e_fw_block_write(adapt, buffer, size);
}