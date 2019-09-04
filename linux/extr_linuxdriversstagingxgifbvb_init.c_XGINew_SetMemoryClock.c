#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vb_device_info {size_t ram_type; int /*<<< orphan*/  P3c4; TYPE_1__* MCLKData; } ;
struct TYPE_4__ {int /*<<< orphan*/  SR30; int /*<<< orphan*/  SR2F; int /*<<< orphan*/  SR2E; } ;
struct TYPE_3__ {int /*<<< orphan*/  SR2A; int /*<<< orphan*/  SR29; int /*<<< orphan*/  SR28; } ;

/* Variables and functions */
 TYPE_2__* XGI340_ECLKData ; 
 int /*<<< orphan*/  xgifb_reg_set (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void XGINew_SetMemoryClock(struct vb_device_info *pVBInfo)
{
	xgifb_reg_set(pVBInfo->P3c4,
		      0x28,
		      pVBInfo->MCLKData[pVBInfo->ram_type].SR28);
	xgifb_reg_set(pVBInfo->P3c4,
		      0x29,
		      pVBInfo->MCLKData[pVBInfo->ram_type].SR29);
	xgifb_reg_set(pVBInfo->P3c4,
		      0x2A,
		      pVBInfo->MCLKData[pVBInfo->ram_type].SR2A);

	xgifb_reg_set(pVBInfo->P3c4,
		      0x2E,
		      XGI340_ECLKData[pVBInfo->ram_type].SR2E);
	xgifb_reg_set(pVBInfo->P3c4,
		      0x2F,
		      XGI340_ECLKData[pVBInfo->ram_type].SR2F);
	xgifb_reg_set(pVBInfo->P3c4,
		      0x30,
		      XGI340_ECLKData[pVBInfo->ram_type].SR30);
}