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
struct xgi_hw_device_info {scalar_t__ jChipType; int /*<<< orphan*/  pjVideoMemoryAddress; } ;
struct xgifb_video_info {int /*<<< orphan*/  vga_base; struct xgi_hw_device_info hw_info; } ;
struct vb_device_info {int XGINew_CR97; int /*<<< orphan*/  P3d4; int /*<<< orphan*/  P3c4; scalar_t__ ram_type; int /*<<< orphan*/  Part4Port; int /*<<< orphan*/  Part2Port; int /*<<< orphan*/  Part1Port; int /*<<< orphan*/  Part0Port; int /*<<< orphan*/  P3c2; int /*<<< orphan*/  FBAddr; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned char GetXG21FPBits (struct vb_device_info*) ; 
 unsigned char GetXG27FPBits (struct vb_device_info*) ; 
 int /*<<< orphan*/  InitTo330Pointer (scalar_t__,struct vb_device_info*) ; 
 int Monitor1Sense ; 
 scalar_t__ XG20 ; 
 scalar_t__ XG21 ; 
 scalar_t__ XG27 ; 
 int XG27_SR36 ; 
 int XG27_SR40 ; 
 int XG27_SR41 ; 
 scalar_t__ XG42 ; 
 int XGI330_CRT2Data_1_2 ; 
 int XGI330_CRT2Data_4_10 ; 
 int XGI330_CRT2Data_4_D ; 
 int XGI330_CRT2Data_4_E ; 
 int XGI330_SR07 ; 
 int XGI330_SR1F ; 
 int XGI330_SR23 ; 
 int XGI330_SR24 ; 
 int XGI330_SR31 ; 
 int XGI330_SR32 ; 
 int XGI330_SR33 ; 
 int* XGI340_AGPReg ; 
 int /*<<< orphan*/  XGINew_ChkSenseStatus (struct vb_device_info*) ; 
 scalar_t__ XGINew_GetXG20DRAMType (struct xgi_hw_device_info*,struct vb_device_info*) ; 
 int /*<<< orphan*/  XGINew_GetXG21Sense (struct pci_dev*,struct vb_device_info*) ; 
 int /*<<< orphan*/  XGINew_GetXG27Sense (struct vb_device_info*) ; 
 int /*<<< orphan*/  XGINew_SetDRAMDefaultRegister340 (struct xgi_hw_device_info*,int /*<<< orphan*/ ,struct vb_device_info*) ; 
 int /*<<< orphan*/  XGINew_SetDRAMSize_340 (struct xgifb_video_info*,struct xgi_hw_device_info*,struct vb_device_info*) ; 
 int /*<<< orphan*/  XGINew_SetModeScratch (struct vb_device_info*) ; 
 int /*<<< orphan*/  XGIRegInit (struct vb_device_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XGI_LockCRT2 (struct vb_device_info*) ; 
 int /*<<< orphan*/  XGI_SenseCRT1 (struct vb_device_info*) ; 
 int /*<<< orphan*/  XGI_UnLockCRT2 (struct vb_device_info*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 struct xgifb_video_info* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int,int*) ; 
 scalar_t__ xgifb_bridge_is_on (struct vb_device_info*) ; 
 int /*<<< orphan*/  xgifb_reg_and_or (int /*<<< orphan*/ ,int,int,unsigned char) ; 
 unsigned char xgifb_reg_get (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xgifb_reg_set (int /*<<< orphan*/ ,int,int) ; 

unsigned char XGIInitNew(struct pci_dev *pdev)
{
	struct xgifb_video_info *xgifb_info = pci_get_drvdata(pdev);
	struct xgi_hw_device_info *HwDeviceExtension = &xgifb_info->hw_info;
	struct vb_device_info VBINF;
	struct vb_device_info *pVBInfo = &VBINF;
	unsigned char i, temp = 0, temp1;

	pVBInfo->FBAddr = HwDeviceExtension->pjVideoMemoryAddress;

	if (!pVBInfo->FBAddr) {
		dev_dbg(&pdev->dev, "pVBInfo->FBAddr == 0\n");
		return 0;
	}

	XGIRegInit(pVBInfo, xgifb_info->vga_base);

	outb(0x67, pVBInfo->P3c2);

	InitTo330Pointer(HwDeviceExtension->jChipType, pVBInfo);

	/* Openkey */
	xgifb_reg_set(pVBInfo->P3c4, 0x05, 0x86);

	/* GetXG21Sense (GPIO) */
	if (HwDeviceExtension->jChipType == XG21)
		XGINew_GetXG21Sense(pdev, pVBInfo);

	if (HwDeviceExtension->jChipType == XG27)
		XGINew_GetXG27Sense(pVBInfo);

	/* Reset Extended register */

	for (i = 0x06; i < 0x20; i++)
		xgifb_reg_set(pVBInfo->P3c4, i, 0);

	for (i = 0x21; i <= 0x27; i++)
		xgifb_reg_set(pVBInfo->P3c4, i, 0);

	for (i = 0x31; i <= 0x3B; i++)
		xgifb_reg_set(pVBInfo->P3c4, i, 0);

	/* Auto over driver for XG42 */
	if (HwDeviceExtension->jChipType == XG42)
		xgifb_reg_set(pVBInfo->P3c4, 0x3B, 0xC0);

	for (i = 0x79; i <= 0x7C; i++)
		xgifb_reg_set(pVBInfo->P3d4, i, 0);

	if (HwDeviceExtension->jChipType >= XG20)
		xgifb_reg_set(pVBInfo->P3d4, 0x97, pVBInfo->XGINew_CR97);

	/* SetDefExt1Regs begin */
	xgifb_reg_set(pVBInfo->P3c4, 0x07, XGI330_SR07);
	if (HwDeviceExtension->jChipType == XG27) {
		xgifb_reg_set(pVBInfo->P3c4, 0x40, XG27_SR40);
		xgifb_reg_set(pVBInfo->P3c4, 0x41, XG27_SR41);
	}
	xgifb_reg_set(pVBInfo->P3c4, 0x11, 0x0F);
	xgifb_reg_set(pVBInfo->P3c4, 0x1F, XGI330_SR1F);
	/* Frame buffer can read/write SR20 */
	xgifb_reg_set(pVBInfo->P3c4, 0x20, 0xA0);
	/* H/W request for slow corner chip */
	xgifb_reg_set(pVBInfo->P3c4, 0x36, 0x70);
	if (HwDeviceExtension->jChipType == XG27)
		xgifb_reg_set(pVBInfo->P3c4, 0x36, XG27_SR36);

	if (HwDeviceExtension->jChipType < XG20) {
		u32 Temp;

		/* Set AGP customize registers (in SetDefAGPRegs) Start */
		for (i = 0x47; i <= 0x4C; i++)
			xgifb_reg_set(pVBInfo->P3d4,
				      i,
				      XGI340_AGPReg[i - 0x47]);

		for (i = 0x70; i <= 0x71; i++)
			xgifb_reg_set(pVBInfo->P3d4,
				      i,
				      XGI340_AGPReg[6 + i - 0x70]);

		for (i = 0x74; i <= 0x77; i++)
			xgifb_reg_set(pVBInfo->P3d4,
				      i,
				      XGI340_AGPReg[8 + i - 0x74]);

		pci_read_config_dword(pdev, 0x50, &Temp);
		Temp >>= 20;
		Temp &= 0xF;

		if (Temp == 1)
			xgifb_reg_set(pVBInfo->P3d4, 0x48, 0x20); /* CR48 */
	} /* != XG20 */

	/* Set PCI */
	xgifb_reg_set(pVBInfo->P3c4, 0x23, XGI330_SR23);
	xgifb_reg_set(pVBInfo->P3c4, 0x24, XGI330_SR24);
	xgifb_reg_set(pVBInfo->P3c4, 0x25, 0);

	if (HwDeviceExtension->jChipType < XG20) {
		/* Set VB */
		XGI_UnLockCRT2(pVBInfo);
		/* disable VideoCapture */
		xgifb_reg_and_or(pVBInfo->Part0Port, 0x3F, 0xEF, 0x00);
		xgifb_reg_set(pVBInfo->Part1Port, 0x00, 0x00);
		/* chk if BCLK>=100MHz */
		temp1 = xgifb_reg_get(pVBInfo->P3d4, 0x7B);

		xgifb_reg_set(pVBInfo->Part1Port,
			      0x02, XGI330_CRT2Data_1_2);

		xgifb_reg_set(pVBInfo->Part1Port, 0x2E, 0x08); /* use VB */
	} /* != XG20 */

	xgifb_reg_set(pVBInfo->P3c4, 0x27, 0x1F);

	if ((HwDeviceExtension->jChipType == XG42) &&
	    XGINew_GetXG20DRAMType(HwDeviceExtension, pVBInfo) != 0) {
		/* Not DDR */
		xgifb_reg_set(pVBInfo->P3c4,
			      0x31,
			      (XGI330_SR31 & 0x3F) | 0x40);
		xgifb_reg_set(pVBInfo->P3c4,
			      0x32,
			      (XGI330_SR32 & 0xFC) | 0x01);
	} else {
		xgifb_reg_set(pVBInfo->P3c4, 0x31, XGI330_SR31);
		xgifb_reg_set(pVBInfo->P3c4, 0x32, XGI330_SR32);
	}
	xgifb_reg_set(pVBInfo->P3c4, 0x33, XGI330_SR33);

	if (HwDeviceExtension->jChipType < XG20) {
		if (xgifb_bridge_is_on(pVBInfo)) {
			xgifb_reg_set(pVBInfo->Part2Port, 0x00, 0x1C);
			xgifb_reg_set(pVBInfo->Part4Port,
				      0x0D, XGI330_CRT2Data_4_D);
			xgifb_reg_set(pVBInfo->Part4Port,
				      0x0E, XGI330_CRT2Data_4_E);
			xgifb_reg_set(pVBInfo->Part4Port,
				      0x10, XGI330_CRT2Data_4_10);
			xgifb_reg_set(pVBInfo->Part4Port, 0x0F, 0x3F);
			XGI_LockCRT2(pVBInfo);
		}
	} /* != XG20 */

	XGI_SenseCRT1(pVBInfo);

	if (HwDeviceExtension->jChipType == XG21) {
		xgifb_reg_and_or(pVBInfo->P3d4,
				 0x32,
				 ~Monitor1Sense,
				 Monitor1Sense); /* Z9 default has CRT */
		temp = GetXG21FPBits(pVBInfo);
		xgifb_reg_and_or(pVBInfo->P3d4, 0x37, ~0x01, temp);
	}
	if (HwDeviceExtension->jChipType == XG27) {
		xgifb_reg_and_or(pVBInfo->P3d4,
				 0x32,
				 ~Monitor1Sense,
				 Monitor1Sense); /* Z9 default has CRT */
		temp = GetXG27FPBits(pVBInfo);
		xgifb_reg_and_or(pVBInfo->P3d4, 0x37, ~0x03, temp);
	}

	pVBInfo->ram_type = XGINew_GetXG20DRAMType(HwDeviceExtension, pVBInfo);

	XGINew_SetDRAMDefaultRegister340(HwDeviceExtension,
					 pVBInfo->P3d4,
					 pVBInfo);

	XGINew_SetDRAMSize_340(xgifb_info, HwDeviceExtension, pVBInfo);

	xgifb_reg_set(pVBInfo->P3c4, 0x22, 0xfa);
	xgifb_reg_set(pVBInfo->P3c4, 0x21, 0xa3);

	XGINew_ChkSenseStatus(pVBInfo);
	XGINew_SetModeScratch(pVBInfo);

	xgifb_reg_set(pVBInfo->P3d4, 0x8c, 0x87);

	return 1;
}