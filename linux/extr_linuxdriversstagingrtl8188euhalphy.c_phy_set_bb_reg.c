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
struct adapter {int dummy; } ;

/* Variables and functions */
 int bMaskDWord ; 
 int cal_bit_shift (int) ; 
 int usb_read32 (struct adapter*,int) ; 
 int /*<<< orphan*/  usb_write32 (struct adapter*,int,int) ; 

void phy_set_bb_reg(struct adapter *adapt, u32 regaddr, u32 bitmask, u32 data)
{
	u32 original_value, bit_shift;

	if (bitmask != bMaskDWord) { /* if not "double word" write */
		original_value = usb_read32(adapt, regaddr);
		bit_shift = cal_bit_shift(bitmask);
		data = (original_value & (~bitmask)) | (data << bit_shift);
	}

	usb_write32(adapt, regaddr, data);
}