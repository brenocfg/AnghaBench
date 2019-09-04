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
typedef  int u32 ;
struct omap_control_phy {int /*<<< orphan*/  otghs_control; } ;

/* Variables and functions */
 int OMAP_CTRL_DEV_AVALID ; 
 int OMAP_CTRL_DEV_IDDIG ; 
 int OMAP_CTRL_DEV_SESSEND ; 
 int OMAP_CTRL_DEV_VBUSVALID ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void omap_control_usb_host_mode(struct omap_control_phy *ctrl_phy)
{
	u32 val;

	val = readl(ctrl_phy->otghs_control);
	val &= ~(OMAP_CTRL_DEV_IDDIG | OMAP_CTRL_DEV_SESSEND);
	val |= OMAP_CTRL_DEV_AVALID | OMAP_CTRL_DEV_VBUSVALID;
	writel(val, ctrl_phy->otghs_control);
}