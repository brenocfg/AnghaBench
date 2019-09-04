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
typedef  int u32 ;
struct ns2_phy_driver {scalar_t__ icfgdrd_regs; scalar_t__ usb2h_strap_reg; TYPE_1__* data; } ;
struct TYPE_2__ {int new_state; } ;

/* Variables and functions */
 int DRD_DEVICE_MODE ; 
 int DRD_HOST_MODE ; 
#define  EVT_DEVICE 129 
#define  EVT_HOST 128 
 int ICFG_DEV_BIT ; 
 scalar_t__ ICFG_DRD_P0CTL ; 
 scalar_t__ ICFG_FSM_CTRL ; 
 int OHCI_OVRCUR_POL ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void connect_change(struct ns2_phy_driver *driver)
{
	u32 extcon_event;
	u32 val;

	extcon_event = driver->data->new_state;
	val = readl(driver->icfgdrd_regs + ICFG_FSM_CTRL);

	switch (extcon_event) {
	case EVT_DEVICE:
		val &= ~(DRD_HOST_MODE | DRD_DEVICE_MODE);
		writel(val, driver->icfgdrd_regs + ICFG_FSM_CTRL);

		val = (val & ~DRD_HOST_MODE) | DRD_DEVICE_MODE;
		writel(val, driver->icfgdrd_regs + ICFG_FSM_CTRL);

		val = readl(driver->icfgdrd_regs + ICFG_DRD_P0CTL);
		val |= ICFG_DEV_BIT;
		writel(val, driver->icfgdrd_regs + ICFG_DRD_P0CTL);
		break;

	case EVT_HOST:
		val &= ~(DRD_HOST_MODE | DRD_DEVICE_MODE);
		writel(val, driver->icfgdrd_regs + ICFG_FSM_CTRL);

		val = (val & ~DRD_DEVICE_MODE) | DRD_HOST_MODE;
		writel(val, driver->icfgdrd_regs + ICFG_FSM_CTRL);

		val = readl(driver->usb2h_strap_reg);
		val |= OHCI_OVRCUR_POL;
		writel(val, driver->usb2h_strap_reg);

		val = readl(driver->icfgdrd_regs + ICFG_DRD_P0CTL);
		val &= ~ICFG_DEV_BIT;
		writel(val, driver->icfgdrd_regs + ICFG_DRD_P0CTL);
		break;

	default:
		pr_err("Invalid extcon event\n");
		break;
	}
}