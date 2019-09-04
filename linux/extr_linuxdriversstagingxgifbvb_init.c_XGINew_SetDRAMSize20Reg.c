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
struct vb_device_info {unsigned short ram_bus; int ram_channel; int /*<<< orphan*/  P3c4; } ;

/* Variables and functions */
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int xgifb_reg_get (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xgifb_reg_set (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static unsigned short XGINew_SetDRAMSize20Reg(
		unsigned short dram_size,
		struct vb_device_info *pVBInfo)
{
	unsigned short data = 0, memsize = 0;
	int RankSize;
	unsigned char ChannelNo;

	RankSize = dram_size * pVBInfo->ram_bus / 8;
	data = xgifb_reg_get(pVBInfo->P3c4, 0x13);
	data &= 0x80;

	if (data == 0x80)
		RankSize *= 2;

	data = 0;

	if (pVBInfo->ram_channel == 3)
		ChannelNo = 4;
	else
		ChannelNo = pVBInfo->ram_channel;

	if (ChannelNo * RankSize <= 256) {
		while ((RankSize >>= 1) > 0)
			data += 0x10;

		memsize = data >> 4;

		/* Fix DRAM Sizing Error */
		xgifb_reg_set(pVBInfo->P3c4,
			      0x14,
			      (xgifb_reg_get(pVBInfo->P3c4, 0x14) & 0x0F) |
				(data & 0xF0));
		usleep_range(15, 1015);
	}
	return memsize;
}