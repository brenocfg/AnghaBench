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
struct xgifb_video_info {int /*<<< orphan*/  hw_info; } ;
struct vb_device_info {int /*<<< orphan*/  P3d4; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCDSense ; 
 int /*<<< orphan*/  XGINew_SenseLCD (int /*<<< orphan*/ *,struct vb_device_info*) ; 
 struct xgifb_video_info* pci_get_drvdata (struct pci_dev*) ; 
 scalar_t__ xgifb_read_vbios (struct pci_dev*) ; 
 int /*<<< orphan*/  xgifb_reg_and (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  xgifb_reg_and_or (int /*<<< orphan*/ ,int,int,unsigned char) ; 
 int xgifb_reg_get (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xgifb_reg_or (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void XGINew_GetXG21Sense(struct pci_dev *pdev,
				struct vb_device_info *pVBInfo)
{
	struct xgifb_video_info *xgifb_info = pci_get_drvdata(pdev);
	unsigned char Temp;

	if (xgifb_read_vbios(pdev)) { /* For XG21 LVDS */
		xgifb_reg_or(pVBInfo->P3d4, 0x32, LCDSense);
		/* LVDS on chip */
		xgifb_reg_and_or(pVBInfo->P3d4, 0x38, ~0xE0, 0xC0);
	} else {
		/* Enable GPIOA/B read */
		xgifb_reg_and_or(pVBInfo->P3d4, 0x4A, ~0x03, 0x03);
		Temp = xgifb_reg_get(pVBInfo->P3d4, 0x48) & 0xC0;
		if (Temp == 0xC0) { /* DVI & DVO GPIOA/B pull high */
			XGINew_SenseLCD(&xgifb_info->hw_info, pVBInfo);
			xgifb_reg_or(pVBInfo->P3d4, 0x32, LCDSense);
			/* Enable read GPIOF */
			xgifb_reg_and_or(pVBInfo->P3d4, 0x4A, ~0x20, 0x20);
			if (xgifb_reg_get(pVBInfo->P3d4, 0x48) & 0x04)
				Temp = 0xA0; /* Only DVO on chip */
			else
				Temp = 0x80; /* TMDS on chip */
			xgifb_reg_and_or(pVBInfo->P3d4, 0x38, ~0xE0, Temp);
			/* Disable read GPIOF */
			xgifb_reg_and(pVBInfo->P3d4, 0x4A, ~0x20);
		}
	}
}