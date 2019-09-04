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
typedef  int /*<<< orphan*/  u32 ;
struct otg_device {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ OMAP_OTG_CTRL ; 
 int /*<<< orphan*/  OMAP_OTG_XCEIV_OUTPUTS ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void omap_otg_ctrl(struct otg_device *otg_dev, u32 outputs)
{
	u32 l;

	l = readl(otg_dev->base + OMAP_OTG_CTRL);
	l &= ~OMAP_OTG_XCEIV_OUTPUTS;
	l |= outputs;
	writel(l, otg_dev->base + OMAP_OTG_CTRL);
}