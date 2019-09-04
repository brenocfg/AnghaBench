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
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  store_pwrindex_offset (struct adapter*,int,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void rtl_addr_delay(struct adapter *adapt,
			   u32 addr, u32 bit_mask, u32 data)
{
	switch (addr) {
	case 0xfe:
		msleep(50);
		break;
	case 0xfd:
		mdelay(5);
		break;
	case 0xfc:
		mdelay(1);
		break;
	case 0xfb:
		udelay(50);
		break;
	case 0xfa:
		udelay(5);
		break;
	case 0xf9:
		udelay(1);
		break;
	default:
		store_pwrindex_offset(adapt, addr, bit_mask, data);
	}
}