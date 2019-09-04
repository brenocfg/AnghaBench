#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct XGI21_LVDSCapStruct {int LVDS_Capability; int LVDSHT; int LVDSVT; int LVDSHDE; int LVDSVDE; int LVDSHFP; int LVDSVFP; int LVDSHSYNC; int LVDSVSYNC; int VCLKData1; int VCLKData2; int PSC_S1; int PSC_S2; int PSC_S3; int PSC_S4; int PSC_S5; } ;
struct TYPE_2__ {int /*<<< orphan*/  P3d4; } ;
struct xgifb_video_info {scalar_t__ display2; struct XGI21_LVDSCapStruct lvds_data; TYPE_1__ dev_info; int /*<<< orphan*/  display2_force; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ XGIFB_DISP_LCD ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct xgifb_video_info* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  vfree (int*) ; 
 int* xgifb_copy_rom (struct pci_dev*,size_t*) ; 
 int xgifb_reg_get (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool xgifb_read_vbios(struct pci_dev *pdev)
{
	struct xgifb_video_info *xgifb_info = pci_get_drvdata(pdev);
	u8 *vbios;
	unsigned long i;
	unsigned char j;
	struct XGI21_LVDSCapStruct *lvds;
	size_t vbios_size;
	int entry;

	vbios = xgifb_copy_rom(pdev, &vbios_size);
	if (!vbios) {
		dev_err(&pdev->dev, "Video BIOS not available\n");
		return false;
	}
	if (vbios_size <= 0x65)
		goto error;
	/*
	 * The user can ignore the LVDS bit in the BIOS and force the display
	 * type.
	 */
	if (!(vbios[0x65] & 0x1) &&
	    (!xgifb_info->display2_force ||
	     xgifb_info->display2 != XGIFB_DISP_LCD)) {
		vfree(vbios);
		return false;
	}
	if (vbios_size <= 0x317)
		goto error;
	i = vbios[0x316] | (vbios[0x317] << 8);
	if (vbios_size <= i - 1)
		goto error;
	j = vbios[i - 1];
	if (j == 0)
		goto error;
	if (j == 0xff)
		j = 1;

	/* Read the LVDS table index scratch register set by the BIOS. */

	entry = xgifb_reg_get(xgifb_info->dev_info.P3d4, 0x36);
	if (entry >= j)
		entry = 0;
	i += entry * 25;
	lvds = &xgifb_info->lvds_data;
	if (vbios_size <= i + 24)
		goto error;
	lvds->LVDS_Capability	= vbios[i]	| (vbios[i + 1] << 8);
	lvds->LVDSHT		= vbios[i + 2]	| (vbios[i + 3] << 8);
	lvds->LVDSVT		= vbios[i + 4]	| (vbios[i + 5] << 8);
	lvds->LVDSHDE		= vbios[i + 6]	| (vbios[i + 7] << 8);
	lvds->LVDSVDE		= vbios[i + 8]	| (vbios[i + 9] << 8);
	lvds->LVDSHFP		= vbios[i + 10]	| (vbios[i + 11] << 8);
	lvds->LVDSVFP		= vbios[i + 12]	| (vbios[i + 13] << 8);
	lvds->LVDSHSYNC		= vbios[i + 14]	| (vbios[i + 15] << 8);
	lvds->LVDSVSYNC		= vbios[i + 16]	| (vbios[i + 17] << 8);
	lvds->VCLKData1		= vbios[i + 18];
	lvds->VCLKData2		= vbios[i + 19];
	lvds->PSC_S1		= vbios[i + 20];
	lvds->PSC_S2		= vbios[i + 21];
	lvds->PSC_S3		= vbios[i + 22];
	lvds->PSC_S4		= vbios[i + 23];
	lvds->PSC_S5		= vbios[i + 24];
	vfree(vbios);
	return true;
error:
	dev_err(&pdev->dev, "Video BIOS corrupted\n");
	vfree(vbios);
	return false;
}