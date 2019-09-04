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
struct vb_device_info {int /*<<< orphan*/  P3c4; } ;

/* Variables and functions */
 int /*<<< orphan*/  xgifb_reg_set (int /*<<< orphan*/ ,unsigned short,int) ; 

__attribute__((used)) static void XGI_ClearExt1Regs(struct vb_device_info *pVBInfo)
{
	unsigned short i;

	for (i = 0x0A; i <= 0x0E; i++)
		xgifb_reg_set(pVBInfo->P3c4, i, 0x00); /* Clear SR0A-SR0E */
}