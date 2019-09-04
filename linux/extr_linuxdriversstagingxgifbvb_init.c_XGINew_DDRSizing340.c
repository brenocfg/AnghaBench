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
typedef  size_t u8 ;
struct xgi_hw_device_info {scalar_t__ jChipType; int ulVideoMemorySize; } ;
struct vb_device_info {int ram_channel; int /*<<< orphan*/  P3c4; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (unsigned short**) ; 
 scalar_t__ XG20 ; 
 int /*<<< orphan*/  XGINew_CheckChannel (struct xgi_hw_device_info*,struct vb_device_info*) ; 
 unsigned short** XGINew_DDRDRAM_TYPE20 ; 
 unsigned short** XGINew_DDRDRAM_TYPE340 ; 
 int XGINew_ReadWriteRest (unsigned short,unsigned short,struct vb_device_info*) ; 
 unsigned short XGINew_SetDRAMSize20Reg (unsigned short const,struct vb_device_info*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  xgifb_reg_and_or (int /*<<< orphan*/ ,int,int,unsigned short const) ; 
 int /*<<< orphan*/  xgifb_reg_set (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int XGINew_DDRSizing340(struct xgi_hw_device_info *HwDeviceExtension,
			       struct vb_device_info *pVBInfo)
{
	u8 i, size;
	unsigned short memsize, start_addr;
	const unsigned short (*dram_table)[2];

	xgifb_reg_set(pVBInfo->P3c4, 0x15, 0x00); /* noninterleaving */
	xgifb_reg_set(pVBInfo->P3c4, 0x1C, 0x00); /* nontiling */
	XGINew_CheckChannel(HwDeviceExtension, pVBInfo);

	if (HwDeviceExtension->jChipType >= XG20) {
		dram_table = XGINew_DDRDRAM_TYPE20;
		size = ARRAY_SIZE(XGINew_DDRDRAM_TYPE20);
		start_addr = 5;
	} else {
		dram_table = XGINew_DDRDRAM_TYPE340;
		size = ARRAY_SIZE(XGINew_DDRDRAM_TYPE340);
		start_addr = 9;
	}

	for (i = 0; i < size; i++) {
		/* SetDRAMSizingType */
		xgifb_reg_and_or(pVBInfo->P3c4, 0x13, 0x80, dram_table[i][1]);
		usleep_range(50, 1050); /* should delay 50 ns */

		memsize = XGINew_SetDRAMSize20Reg(dram_table[i][0], pVBInfo);

		if (memsize == 0)
			continue;

		memsize += (pVBInfo->ram_channel - 2) + 20;
		if ((HwDeviceExtension->ulVideoMemorySize - 1) <
			(unsigned long)(1 << memsize))
			continue;

		if (XGINew_ReadWriteRest(memsize, start_addr, pVBInfo) == 1)
			return 1;
	}
	return 0;
}