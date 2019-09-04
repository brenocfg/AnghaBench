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
struct dwc3_omap {scalar_t__ irqmisc_offset; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 scalar_t__ USBOTGSS_IRQSTATUS_RAW_MISC ; 
 int /*<<< orphan*/  dwc3_omap_readl (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static u32 dwc3_omap_read_irqmisc_status(struct dwc3_omap *omap)
{
	return dwc3_omap_readl(omap->base, USBOTGSS_IRQSTATUS_RAW_MISC +
						omap->irqmisc_offset);
}