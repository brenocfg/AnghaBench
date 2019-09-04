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
struct xgi_hw_device_info {scalar_t__ jChipType; } ;
struct vb_device_info {int** CR40; size_t ram_type; } ;

/* Variables and functions */
 scalar_t__ XG27 ; 
 int XG27_CR8F ; 
 int XG40_CRCF ; 
 scalar_t__ XG42 ; 
 int /*<<< orphan*/  XGINew_DDR1x_DefaultRegister (struct xgi_hw_device_info*,unsigned long,struct vb_device_info*) ; 
 int /*<<< orphan*/  XGINew_DDR2_DefaultRegister (struct xgi_hw_device_info*,unsigned long,struct vb_device_info*) ; 
 unsigned char XGINew_GetXG20DRAMType (struct xgi_hw_device_info*,struct vb_device_info*) ; 
 int /*<<< orphan*/  XGI_SetDRAM_Helper (unsigned long,unsigned char,unsigned char,int,int,int,int) ; 
 int /*<<< orphan*/  xgifb_reg_and_or (unsigned long,int,int,unsigned char) ; 
 int /*<<< orphan*/  xgifb_reg_or (unsigned long,int,unsigned char) ; 
 int /*<<< orphan*/  xgifb_reg_set (unsigned long,int,int) ; 

__attribute__((used)) static void XGINew_SetDRAMDefaultRegister340(
		struct xgi_hw_device_info *HwDeviceExtension,
		unsigned long Port, struct vb_device_info *pVBInfo)
{
	unsigned char temp, temp1, temp2, temp3, j, k;

	unsigned long P3d4 = Port, P3c4 = Port - 0x10;

	xgifb_reg_set(P3d4, 0x6D, pVBInfo->CR40[8][pVBInfo->ram_type]);
	xgifb_reg_set(P3d4, 0x68, pVBInfo->CR40[5][pVBInfo->ram_type]);
	xgifb_reg_set(P3d4, 0x69, pVBInfo->CR40[6][pVBInfo->ram_type]);
	xgifb_reg_set(P3d4, 0x6A, pVBInfo->CR40[7][pVBInfo->ram_type]);

	/* CR6B DQS fine tune delay */
	temp = 0xaa;
	XGI_SetDRAM_Helper(P3d4, temp, 0, 0x6B, 2, 0xF0, 0x10);

	/* CR6E DQM fine tune delay */
	XGI_SetDRAM_Helper(P3d4, 0, 0, 0x6E, 2, 0xF0, 0x10);

	temp3 = 0;
	for (k = 0; k < 4; k++) {
		/* CR6E_D[1:0] select channel */
		xgifb_reg_and_or(P3d4, 0x6E, 0xFC, temp3);
		XGI_SetDRAM_Helper(P3d4, 0, 0, 0x6F, 0, 0xF8, 0x08);
		temp3 += 0x01;
	}

	xgifb_reg_set(P3d4,
		      0x80,
		      pVBInfo->CR40[9][pVBInfo->ram_type]); /* CR80 */
	xgifb_reg_set(P3d4,
		      0x81,
		      pVBInfo->CR40[10][pVBInfo->ram_type]); /* CR81 */

	temp2 = 0x80;
	/* CR89 terminator type select */
	XGI_SetDRAM_Helper(P3d4, 0, temp2, 0x89, 0, 0xF0, 0x10);

	temp = 0;
	temp1 = temp & 0x03;
	temp2 |= temp1;
	xgifb_reg_set(P3d4, 0x89, temp2);

	temp = pVBInfo->CR40[3][pVBInfo->ram_type];
	temp1 = temp & 0x0F;
	temp2 = (temp >> 4) & 0x07;
	temp3 = temp & 0x80;
	xgifb_reg_set(P3d4, 0x45, temp1); /* CR45 */
	xgifb_reg_set(P3d4, 0x99, temp2); /* CR99 */
	xgifb_reg_or(P3d4, 0x40, temp3); /* CR40_D[7] */
	xgifb_reg_set(P3d4,
		      0x41,
		      pVBInfo->CR40[0][pVBInfo->ram_type]); /* CR41 */

	if (HwDeviceExtension->jChipType == XG27)
		xgifb_reg_set(P3d4, 0x8F, XG27_CR8F); /* CR8F */

	for (j = 0; j <= 6; j++) /* CR90 - CR96 */
		xgifb_reg_set(P3d4, (0x90 + j),
			      pVBInfo->CR40[14 + j][pVBInfo->ram_type]);

	for (j = 0; j <= 2; j++) /* CRC3 - CRC5 */
		xgifb_reg_set(P3d4, (0xC3 + j),
			      pVBInfo->CR40[21 + j][pVBInfo->ram_type]);

	for (j = 0; j < 2; j++) /* CR8A - CR8B */
		xgifb_reg_set(P3d4, (0x8A + j),
			      pVBInfo->CR40[1 + j][pVBInfo->ram_type]);

	if (HwDeviceExtension->jChipType == XG42)
		xgifb_reg_set(P3d4, 0x8C, 0x87);

	xgifb_reg_set(P3d4,
		      0x59,
		      pVBInfo->CR40[4][pVBInfo->ram_type]); /* CR59 */

	xgifb_reg_set(P3d4, 0x83, 0x09); /* CR83 */
	xgifb_reg_set(P3d4, 0x87, 0x00); /* CR87 */
	xgifb_reg_set(P3d4, 0xCF, XG40_CRCF); /* CRCF */
	if (pVBInfo->ram_type) {
		xgifb_reg_set(P3c4, 0x17, 0x80); /* SR17 DDRII */
		if (HwDeviceExtension->jChipType == XG27)
			xgifb_reg_set(P3c4, 0x17, 0x02); /* SR17 DDRII */

	} else {
		xgifb_reg_set(P3c4, 0x17, 0x00); /* SR17 DDR */
	}
	xgifb_reg_set(P3c4, 0x1A, 0x87); /* SR1A */

	temp = XGINew_GetXG20DRAMType(HwDeviceExtension, pVBInfo);
	if (temp == 0) {
		XGINew_DDR1x_DefaultRegister(HwDeviceExtension, P3d4, pVBInfo);
	} else {
		xgifb_reg_set(P3d4, 0xB0, 0x80); /* DDRII Dual frequency mode */
		XGINew_DDR2_DefaultRegister(HwDeviceExtension, P3d4, pVBInfo);
	}
	xgifb_reg_set(P3c4, 0x1B, 0x03); /* SR1B */
}