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
struct isp1760_device {int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int HW_DP_PULLUP ; 
 int /*<<< orphan*/  HW_OTG_CTRL_SET ; 
 int /*<<< orphan*/  isp1760_write32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void isp1760_set_pullup(struct isp1760_device *isp, bool enable)
{
	isp1760_write32(isp->regs, HW_OTG_CTRL_SET,
			enable ? HW_DP_PULLUP : HW_DP_PULLUP << 16);
}