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
struct TYPE_2__ {int /*<<< orphan*/  PSC_S3; int /*<<< orphan*/  PSC_S2; } ;
struct xgifb_video_info {TYPE_1__ lvds_data; } ;
struct xgi_hw_device_info {scalar_t__ jChipType; } ;
struct vb_device_info {int IF_DEF_LVDS; int /*<<< orphan*/  P3c4; } ;

/* Variables and functions */
 scalar_t__ XG21 ; 
 scalar_t__ XG27 ; 
 int /*<<< orphan*/  XGI_XG21BLSignalVDD (int,int,struct vb_device_info*) ; 
 int XGI_XG21GetPSCValue (struct vb_device_info*) ; 
 int /*<<< orphan*/  XGI_XG27BLSignalVDD (int,int,struct vb_device_info*) ; 
 int XGI_XG27GetPSCValue (struct vb_device_info*) ; 
 int /*<<< orphan*/  mdelay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgifb_reg_and_or (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void XGI_DisplayOn(struct xgifb_video_info *xgifb_info,
			  struct xgi_hw_device_info *pXGIHWDE,
			  struct vb_device_info *pVBInfo)
{
	xgifb_reg_and_or(pVBInfo->P3c4, 0x01, 0xDF, 0x00);
	if (pXGIHWDE->jChipType == XG21) {
		if (pVBInfo->IF_DEF_LVDS == 1) {
			if (!(XGI_XG21GetPSCValue(pVBInfo) & 0x1)) {
				/* LVDS VDD on */
				XGI_XG21BLSignalVDD(0x01, 0x01, pVBInfo);
				mdelay(xgifb_info->lvds_data.PSC_S2);
			}
			if (!(XGI_XG21GetPSCValue(pVBInfo) & 0x20))
				/* LVDS signal on */
				XGI_XG21BLSignalVDD(0x20, 0x20, pVBInfo);
			mdelay(xgifb_info->lvds_data.PSC_S3);
			/* LVDS backlight on */
			XGI_XG21BLSignalVDD(0x02, 0x02, pVBInfo);
		} else {
			/* DVO/DVI signal on */
			XGI_XG21BLSignalVDD(0x20, 0x20, pVBInfo);
		}
	}

	if (pXGIHWDE->jChipType == XG27) {
		if (pVBInfo->IF_DEF_LVDS == 1) {
			if (!(XGI_XG27GetPSCValue(pVBInfo) & 0x1)) {
				/* LVDS VDD on */
				XGI_XG27BLSignalVDD(0x01, 0x01, pVBInfo);
				mdelay(xgifb_info->lvds_data.PSC_S2);
			}
			if (!(XGI_XG27GetPSCValue(pVBInfo) & 0x20))
				/* LVDS signal on */
				XGI_XG27BLSignalVDD(0x20, 0x20, pVBInfo);
			mdelay(xgifb_info->lvds_data.PSC_S3);
			/* LVDS backlight on */
			XGI_XG27BLSignalVDD(0x02, 0x02, pVBInfo);
		} else {
			/* DVO/DVI signal on */
			XGI_XG27BLSignalVDD(0x20, 0x20, pVBInfo);
		}
	}
}