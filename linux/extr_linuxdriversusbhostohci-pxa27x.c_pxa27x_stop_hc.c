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
typedef  int uint32_t ;
struct usb_hcd {int /*<<< orphan*/  self; } ;
struct pxaohci_platform_data {int /*<<< orphan*/  (* exit ) (struct device*) ;} ;
struct pxa27x_ohci {int /*<<< orphan*/  clk; scalar_t__ mmio_base; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ UHCCOMS ; 
 int __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (int,scalar_t__) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_is_pxa3xx () ; 
 struct usb_hcd* dev_get_drvdata (struct device*) ; 
 struct pxaohci_platform_data* dev_get_platdata (struct device*) ; 
 int /*<<< orphan*/  pxa27x_reset_hc (struct pxa27x_ohci*) ; 
 int /*<<< orphan*/  pxa3xx_u2d_stop_hc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct device*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void pxa27x_stop_hc(struct pxa27x_ohci *pxa_ohci, struct device *dev)
{
	struct pxaohci_platform_data *inf;
	struct usb_hcd *hcd = dev_get_drvdata(dev);
	uint32_t uhccoms;

	inf = dev_get_platdata(dev);

	if (cpu_is_pxa3xx())
		pxa3xx_u2d_stop_hc(&hcd->self);

	if (inf->exit)
		inf->exit(dev);

	pxa27x_reset_hc(pxa_ohci);

	/* Host Controller Reset */
	uhccoms = __raw_readl(pxa_ohci->mmio_base + UHCCOMS) | 0x01;
	__raw_writel(uhccoms, pxa_ohci->mmio_base + UHCCOMS);
	udelay(10);

	clk_disable_unprepare(pxa_ohci->clk);
}