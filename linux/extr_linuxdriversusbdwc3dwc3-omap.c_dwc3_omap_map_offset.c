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
struct dwc3_omap {int /*<<< orphan*/  debug_offset; int /*<<< orphan*/  utmi_otg_offset; int /*<<< orphan*/  irqmisc_offset; int /*<<< orphan*/  irq0_offset; int /*<<< orphan*/  irq_eoi_offset; TYPE_1__* dev; } ;
struct device_node {int dummy; } ;
struct TYPE_2__ {struct device_node* of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  USBOTGSS_DEBUG_OFFSET ; 
 int /*<<< orphan*/  USBOTGSS_EOI_OFFSET ; 
 int /*<<< orphan*/  USBOTGSS_IRQ0_OFFSET ; 
 int /*<<< orphan*/  USBOTGSS_IRQMISC_OFFSET ; 
 int /*<<< orphan*/  USBOTGSS_UTMI_OTG_OFFSET ; 
 scalar_t__ of_device_is_compatible (struct device_node*,char*) ; 

__attribute__((used)) static void dwc3_omap_map_offset(struct dwc3_omap *omap)
{
	struct device_node	*node = omap->dev->of_node;

	/*
	 * Differentiate between OMAP5 and AM437x.
	 *
	 * For OMAP5(ES2.0) and AM437x wrapper revision is same, even
	 * though there are changes in wrapper register offsets.
	 *
	 * Using dt compatible to differentiate AM437x.
	 */
	if (of_device_is_compatible(node, "ti,am437x-dwc3")) {
		omap->irq_eoi_offset = USBOTGSS_EOI_OFFSET;
		omap->irq0_offset = USBOTGSS_IRQ0_OFFSET;
		omap->irqmisc_offset = USBOTGSS_IRQMISC_OFFSET;
		omap->utmi_otg_offset = USBOTGSS_UTMI_OTG_OFFSET;
		omap->debug_offset = USBOTGSS_DEBUG_OFFSET;
	}
}