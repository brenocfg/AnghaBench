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
struct xgi_hw_device_info {int dummy; } ;
struct vb_device_info {int /*<<< orphan*/  ram_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  XGINew_GetXG20DRAMType (struct xgi_hw_device_info*,struct vb_device_info*) ; 
 int /*<<< orphan*/  XGINew_SetMemoryClock (struct vb_device_info*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  xgifb_reg_set (unsigned long,int,int) ; 

__attribute__((used)) static void XGINew_DDR2_MRS_XG20(struct xgi_hw_device_info *HwDeviceExtension,
				 unsigned long P3c4,
				 struct vb_device_info *pVBInfo)
{
	unsigned long P3d4 = P3c4 + 0x10;

	pVBInfo->ram_type = XGINew_GetXG20DRAMType(HwDeviceExtension, pVBInfo);
	XGINew_SetMemoryClock(pVBInfo);

	xgifb_reg_set(P3d4, 0x97, 0x11); /* CR97 */

	usleep_range(200, 1200);
	xgifb_reg_set(P3c4, 0x18, 0x00); /* EMRS2 */
	xgifb_reg_set(P3c4, 0x19, 0x80);
	xgifb_reg_set(P3c4, 0x16, 0x05);
	xgifb_reg_set(P3c4, 0x16, 0x85);

	xgifb_reg_set(P3c4, 0x18, 0x00); /* EMRS3 */
	xgifb_reg_set(P3c4, 0x19, 0xC0);
	xgifb_reg_set(P3c4, 0x16, 0x05);
	xgifb_reg_set(P3c4, 0x16, 0x85);

	xgifb_reg_set(P3c4, 0x18, 0x00); /* EMRS1 */
	xgifb_reg_set(P3c4, 0x19, 0x40);
	xgifb_reg_set(P3c4, 0x16, 0x05);
	xgifb_reg_set(P3c4, 0x16, 0x85);

	xgifb_reg_set(P3c4, 0x18, 0x42); /* MRS1 */
	xgifb_reg_set(P3c4, 0x19, 0x02);
	xgifb_reg_set(P3c4, 0x16, 0x05);
	xgifb_reg_set(P3c4, 0x16, 0x85);

	usleep_range(15, 1015);
	xgifb_reg_set(P3c4, 0x1B, 0x04); /* SR1B */
	usleep_range(30, 1030);
	xgifb_reg_set(P3c4, 0x1B, 0x00); /* SR1B */
	usleep_range(100, 1100);

	xgifb_reg_set(P3c4, 0x18, 0x42); /* MRS1 */
	xgifb_reg_set(P3c4, 0x19, 0x00);
	xgifb_reg_set(P3c4, 0x16, 0x05);
	xgifb_reg_set(P3c4, 0x16, 0x85);

	usleep_range(200, 1200);
}