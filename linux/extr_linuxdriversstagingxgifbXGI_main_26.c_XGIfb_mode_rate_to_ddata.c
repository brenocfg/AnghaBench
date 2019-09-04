#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct xgi_hw_device_info {int /*<<< orphan*/  jChipType; } ;
struct vb_device_info {int dummy; } ;
struct TYPE_6__ {int Ext_ModeID; int Ext_ModeFlag; } ;
struct TYPE_5__ {unsigned short Ext_CRT1CRTC; int XRes; unsigned short YRes; int Ext_InfoFlag; int ModeID; } ;
struct TYPE_4__ {unsigned char* CR; } ;

/* Variables and functions */
 int DoubleScanMode ; 
 int FB_SYNC_HOR_HIGH_ACT ; 
 int FB_SYNC_VERT_HIGH_ACT ; 
 int FB_VMODE_DOUBLE ; 
 int FB_VMODE_INTERLACED ; 
 int FB_VMODE_NONINTERLACED ; 
 int /*<<< orphan*/  InitTo330Pointer (int /*<<< orphan*/ ,struct vb_device_info*) ; 
 TYPE_3__* XGI330_EModeIDTable ; 
 TYPE_2__* XGI330_RefIndex ; 
 TYPE_1__* XGI_CRT1Table ; 
 unsigned short XGI_GetRatePtrCRT2 (struct xgi_hw_device_info*,unsigned short,unsigned short,struct vb_device_info*) ; 
 int /*<<< orphan*/  XGI_SearchModeID (unsigned short,unsigned short*) ; 

__attribute__((used)) static int XGIfb_mode_rate_to_ddata(struct vb_device_info *XGI_Pr,
				    struct xgi_hw_device_info *HwDeviceExtension,
				    unsigned char modeno, u32 *left_margin,
				    u32 *right_margin, u32 *upper_margin,
				    u32 *lower_margin, u32 *hsync_len,
				    u32 *vsync_len, u32 *sync, u32 *vmode)
{
	unsigned short ModeNo = modeno;
	unsigned short ModeIdIndex, index = 0;
	unsigned short RefreshRateTableIndex = 0;

	unsigned short VRE, VBE, VRS, VDE;
	unsigned short HRE, HBE, HRS, HDE;
	unsigned char sr_data, cr_data, cr_data2;
	int B, C, D, F, temp, j;

	InitTo330Pointer(HwDeviceExtension->jChipType, XGI_Pr);
	if (!XGI_SearchModeID(ModeNo, &ModeIdIndex))
		return 0;
	RefreshRateTableIndex = XGI_GetRatePtrCRT2(HwDeviceExtension, ModeNo,
						   ModeIdIndex, XGI_Pr);
	index = XGI330_RefIndex[RefreshRateTableIndex].Ext_CRT1CRTC;

	sr_data = XGI_CRT1Table[index].CR[5];

	HDE = XGI330_RefIndex[RefreshRateTableIndex].XRes >> 3;

	cr_data = XGI_CRT1Table[index].CR[3];

	/* Horizontal retrace (=sync) start */
	HRS = (cr_data & 0xff) | ((unsigned short)(sr_data & 0xC0) << 2);
	F = HRS - HDE - 3;

	sr_data = XGI_CRT1Table[index].CR[6];

	cr_data = XGI_CRT1Table[index].CR[2];

	cr_data2 = XGI_CRT1Table[index].CR[4];

	/* Horizontal blank end */
	HBE = (cr_data & 0x1f) | ((unsigned short)(cr_data2 & 0x80) >> 2)
			| ((unsigned short)(sr_data & 0x03) << 6);

	/* Horizontal retrace (=sync) end */
	HRE = (cr_data2 & 0x1f) | ((sr_data & 0x04) << 3);

	temp = HBE - ((HDE - 1) & 255);
	B = (temp > 0) ? temp : (temp + 256);

	temp = HRE - ((HDE + F + 3) & 63);
	C = (temp > 0) ? temp : (temp + 64);

	D = B - F - C;

	*left_margin = D * 8;
	*right_margin = F * 8;
	*hsync_len = C * 8;

	sr_data = XGI_CRT1Table[index].CR[14];

	cr_data2 = XGI_CRT1Table[index].CR[9];

	VDE = XGI330_RefIndex[RefreshRateTableIndex].YRes;

	cr_data = XGI_CRT1Table[index].CR[10];

	/* Vertical retrace (=sync) start */
	VRS = (cr_data & 0xff) | ((unsigned short)(cr_data2 & 0x04) << 6)
			| ((unsigned short)(cr_data2 & 0x80) << 2)
			| ((unsigned short)(sr_data & 0x08) << 7);
	F = VRS + 1 - VDE;

	cr_data = XGI_CRT1Table[index].CR[13];

	/* Vertical blank end */
	VBE = (cr_data & 0xff) | ((unsigned short)(sr_data & 0x10) << 4);
	temp = VBE - ((VDE - 1) & 511);
	B = (temp > 0) ? temp : (temp + 512);

	cr_data = XGI_CRT1Table[index].CR[11];

	/* Vertical retrace (=sync) end */
	VRE = (cr_data & 0x0f) | ((sr_data & 0x20) >> 1);
	temp = VRE - ((VDE + F - 1) & 31);
	C = (temp > 0) ? temp : (temp + 32);

	D = B - F - C;

	*upper_margin = D;
	*lower_margin = F;
	*vsync_len = C;

	if (XGI330_RefIndex[RefreshRateTableIndex].Ext_InfoFlag & 0x8000)
		*sync &= ~FB_SYNC_VERT_HIGH_ACT;
	else
		*sync |= FB_SYNC_VERT_HIGH_ACT;

	if (XGI330_RefIndex[RefreshRateTableIndex].Ext_InfoFlag & 0x4000)
		*sync &= ~FB_SYNC_HOR_HIGH_ACT;
	else
		*sync |= FB_SYNC_HOR_HIGH_ACT;

	*vmode = FB_VMODE_NONINTERLACED;
	if (XGI330_RefIndex[RefreshRateTableIndex].Ext_InfoFlag & 0x0080) {
		*vmode = FB_VMODE_INTERLACED;
	} else {
		j = 0;
		while (XGI330_EModeIDTable[j].Ext_ModeID != 0xff) {
			if (XGI330_EModeIDTable[j].Ext_ModeID ==
			    XGI330_RefIndex[RefreshRateTableIndex].ModeID) {
				if (XGI330_EModeIDTable[j].Ext_ModeFlag &
				    DoubleScanMode) {
					*vmode = FB_VMODE_DOUBLE;
				}
				break;
			}
			j++;
		}
	}

	return 1;
}