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
struct vb_device_info {int* SR18; size_t ram_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  xgifb_reg_set (unsigned long,int,int) ; 

__attribute__((used)) static void XGINew_DDR1x_MRS_340(unsigned long P3c4,
				 struct vb_device_info *pVBInfo)
{
	xgifb_reg_set(P3c4, 0x18, 0x01);
	xgifb_reg_set(P3c4, 0x19, 0x20);
	xgifb_reg_set(P3c4, 0x16, 0x00);
	xgifb_reg_set(P3c4, 0x16, 0x80);

	usleep_range(3, 1003);
	xgifb_reg_set(P3c4, 0x18, 0x00);
	xgifb_reg_set(P3c4, 0x19, 0x20);
	xgifb_reg_set(P3c4, 0x16, 0x00);
	xgifb_reg_set(P3c4, 0x16, 0x80);

	usleep_range(60, 1060);
	xgifb_reg_set(P3c4, 0x18, pVBInfo->SR18[pVBInfo->ram_type]); /* SR18 */
	xgifb_reg_set(P3c4, 0x19, 0x01);
	xgifb_reg_set(P3c4, 0x16, 0x03);
	xgifb_reg_set(P3c4, 0x16, 0x83);
	usleep_range(1, 1001);
	xgifb_reg_set(P3c4, 0x1B, 0x03);
	usleep_range(500, 1500);
	xgifb_reg_set(P3c4, 0x18, pVBInfo->SR18[pVBInfo->ram_type]); /* SR18 */
	xgifb_reg_set(P3c4, 0x19, 0x00);
	xgifb_reg_set(P3c4, 0x16, 0x03);
	xgifb_reg_set(P3c4, 0x16, 0x83);
	xgifb_reg_set(P3c4, 0x1B, 0x00);
}