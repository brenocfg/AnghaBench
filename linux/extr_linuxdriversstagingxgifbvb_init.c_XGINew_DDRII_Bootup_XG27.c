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
struct vb_device_info {int XGINew_CR97; int /*<<< orphan*/  ram_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  XGINew_GetXG20DRAMType (struct xgi_hw_device_info*,struct vb_device_info*) ; 
 int /*<<< orphan*/  XGINew_SetMemoryClock (struct vb_device_info*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  xgifb_reg_set (unsigned long,int,int) ; 

__attribute__((used)) static void XGINew_DDRII_Bootup_XG27(
			struct xgi_hw_device_info *HwDeviceExtension,
			unsigned long P3c4, struct vb_device_info *pVBInfo)
{
	unsigned long P3d4 = P3c4 + 0x10;

	pVBInfo->ram_type = XGINew_GetXG20DRAMType(HwDeviceExtension, pVBInfo);
	XGINew_SetMemoryClock(pVBInfo);

	/* Set Double Frequency */
	xgifb_reg_set(P3d4, 0x97, pVBInfo->XGINew_CR97); /* CR97 */

	usleep_range(200, 1200);

	xgifb_reg_set(P3c4, 0x18, 0x00); /* Set SR18 */ /* EMRS2 */
	xgifb_reg_set(P3c4, 0x19, 0x80); /* Set SR19 */
	xgifb_reg_set(P3c4, 0x16, 0x20); /* Set SR16 */
	usleep_range(15, 1015);
	xgifb_reg_set(P3c4, 0x16, 0xA0); /* Set SR16 */
	usleep_range(15, 1015);

	xgifb_reg_set(P3c4, 0x18, 0x00); /* Set SR18 */ /* EMRS3 */
	xgifb_reg_set(P3c4, 0x19, 0xC0); /* Set SR19 */
	xgifb_reg_set(P3c4, 0x16, 0x20); /* Set SR16 */
	usleep_range(15, 1015);
	xgifb_reg_set(P3c4, 0x16, 0xA0); /* Set SR16 */
	usleep_range(15, 1015);

	xgifb_reg_set(P3c4, 0x18, 0x00); /* Set SR18 */ /* EMRS1 */
	xgifb_reg_set(P3c4, 0x19, 0x40); /* Set SR19 */
	xgifb_reg_set(P3c4, 0x16, 0x20); /* Set SR16 */
	usleep_range(30, 1030);
	xgifb_reg_set(P3c4, 0x16, 0xA0); /* Set SR16 */
	usleep_range(15, 1015);

	xgifb_reg_set(P3c4, 0x18, 0x42); /* Set SR18 */ /* MRS, DLL Enable */
	xgifb_reg_set(P3c4, 0x19, 0x0A); /* Set SR19 */
	xgifb_reg_set(P3c4, 0x16, 0x00); /* Set SR16 */
	usleep_range(30, 1030);
	xgifb_reg_set(P3c4, 0x16, 0x00); /* Set SR16 */
	xgifb_reg_set(P3c4, 0x16, 0x80); /* Set SR16 */

	xgifb_reg_set(P3c4, 0x1B, 0x04); /* Set SR1B */
	usleep_range(60, 1060);
	xgifb_reg_set(P3c4, 0x1B, 0x00); /* Set SR1B */

	xgifb_reg_set(P3c4, 0x18, 0x42); /* Set SR18 */ /* MRS, DLL Reset */
	xgifb_reg_set(P3c4, 0x19, 0x08); /* Set SR19 */
	xgifb_reg_set(P3c4, 0x16, 0x00); /* Set SR16 */

	usleep_range(30, 1030);
	xgifb_reg_set(P3c4, 0x16, 0x83); /* Set SR16 */
	usleep_range(15, 1015);

	xgifb_reg_set(P3c4, 0x18, 0x80); /* Set SR18 */ /* MRS, ODT */
	xgifb_reg_set(P3c4, 0x19, 0x46); /* Set SR19 */
	xgifb_reg_set(P3c4, 0x16, 0x20); /* Set SR16 */
	usleep_range(30, 1030);
	xgifb_reg_set(P3c4, 0x16, 0xA0); /* Set SR16 */
	usleep_range(15, 1015);

	xgifb_reg_set(P3c4, 0x18, 0x00); /* Set SR18 */ /* EMRS */
	xgifb_reg_set(P3c4, 0x19, 0x40); /* Set SR19 */
	xgifb_reg_set(P3c4, 0x16, 0x20); /* Set SR16 */
	usleep_range(30, 1030);
	xgifb_reg_set(P3c4, 0x16, 0xA0); /* Set SR16 */
	usleep_range(15, 1015);

	/* Set SR1B refresh control 000:close; 010:open */
	xgifb_reg_set(P3c4, 0x1B, 0x04);
	usleep_range(200, 1200);
}