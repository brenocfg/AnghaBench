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
struct vb_device_info {int /*<<< orphan*/  P3c4; } ;
struct TYPE_2__ {int /*<<< orphan*/  SR2C; int /*<<< orphan*/  SR2B; } ;

/* Variables and functions */
 TYPE_1__* XGI_VCLKData ; 
 int /*<<< orphan*/  xgifb_reg_and (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  xgifb_reg_and_or (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  xgifb_reg_set (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned char XGI_SetDefaultVCLK(struct vb_device_info *pVBInfo)
{
	xgifb_reg_and_or(pVBInfo->P3c4, 0x31, ~0x30, 0x20);
	xgifb_reg_set(pVBInfo->P3c4, 0x2B, XGI_VCLKData[0].SR2B);
	xgifb_reg_set(pVBInfo->P3c4, 0x2C, XGI_VCLKData[0].SR2C);

	xgifb_reg_and_or(pVBInfo->P3c4, 0x31, ~0x30, 0x10);
	xgifb_reg_set(pVBInfo->P3c4, 0x2B, XGI_VCLKData[1].SR2B);
	xgifb_reg_set(pVBInfo->P3c4, 0x2C, XGI_VCLKData[1].SR2C);

	xgifb_reg_and(pVBInfo->P3c4, 0x31, ~0x30);
	return 0;
}