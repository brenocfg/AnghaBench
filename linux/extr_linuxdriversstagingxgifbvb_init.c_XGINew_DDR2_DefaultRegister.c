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
 int /*<<< orphan*/  XGINew_DDR2_MRS_XG20 (struct xgi_hw_device_info*,unsigned long,struct vb_device_info*) ; 
 int /*<<< orphan*/  XGINew_DDRII_Bootup_XG27 (struct xgi_hw_device_info*,unsigned long,struct vb_device_info*) ; 
 int /*<<< orphan*/  xgifb_reg_get (unsigned long,int) ; 
 int /*<<< orphan*/  xgifb_reg_set (unsigned long,int,int) ; 

__attribute__((used)) static void XGINew_DDR2_DefaultRegister(
		struct xgi_hw_device_info *HwDeviceExtension,
		unsigned long Port, struct vb_device_info *pVBInfo)
{
	unsigned long P3d4 = Port, P3c4 = Port - 0x10;
	/*
	 * keep following setting sequence, each setting in
	 * the same reg insert idle
	 */
	xgifb_reg_set(P3d4, 0x82, 0x77);
	xgifb_reg_set(P3d4, 0x86, 0x00);
	xgifb_reg_get(P3d4, 0x86); /* Insert read command for delay */
	xgifb_reg_set(P3d4, 0x86, 0x88);
	xgifb_reg_get(P3d4, 0x86); /* Insert read command for delay */
	/* CR86 */
	xgifb_reg_set(P3d4, 0x86, pVBInfo->CR40[13][pVBInfo->ram_type]);
	xgifb_reg_set(P3d4, 0x82, 0x77);
	xgifb_reg_set(P3d4, 0x85, 0x00);
	xgifb_reg_get(P3d4, 0x85); /* Insert read command for delay */
	xgifb_reg_set(P3d4, 0x85, 0x88);
	xgifb_reg_get(P3d4, 0x85); /* Insert read command for delay */
	xgifb_reg_set(P3d4,
		      0x85,
		      pVBInfo->CR40[12][pVBInfo->ram_type]); /* CR85 */
	if (HwDeviceExtension->jChipType == XG27)
		/* CR82 */
		xgifb_reg_set(P3d4, 0x82, pVBInfo->CR40[11][pVBInfo->ram_type]);
	else
		xgifb_reg_set(P3d4, 0x82, 0xA8); /* CR82 */

	xgifb_reg_set(P3d4, 0x98, 0x01);
	xgifb_reg_set(P3d4, 0x9A, 0x02);
	if (HwDeviceExtension->jChipType == XG27)
		XGINew_DDRII_Bootup_XG27(HwDeviceExtension, P3c4, pVBInfo);
	else
		XGINew_DDR2_MRS_XG20(HwDeviceExtension, P3c4, pVBInfo);
}