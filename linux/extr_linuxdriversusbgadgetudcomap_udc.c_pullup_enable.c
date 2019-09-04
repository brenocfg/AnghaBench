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
typedef  int /*<<< orphan*/  u16 ;
struct omap_udc {int /*<<< orphan*/  gadget; } ;

/* Variables and functions */
 int /*<<< orphan*/  OTG_BSESSVLD ; 
 int /*<<< orphan*/  OTG_CTRL ; 
 int /*<<< orphan*/  UDC_DS_CHG_IE ; 
 int /*<<< orphan*/  UDC_IRQ_EN ; 
 int /*<<< orphan*/  UDC_PULLUP_EN ; 
 int /*<<< orphan*/  UDC_SYSCON1 ; 
 int /*<<< orphan*/  cpu_is_omap15xx () ; 
 int /*<<< orphan*/  gadget_is_otg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_readw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_writew (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pullup_enable(struct omap_udc *udc)
{
	u16 w;

	w = omap_readw(UDC_SYSCON1);
	w |= UDC_PULLUP_EN;
	omap_writew(w, UDC_SYSCON1);
	if (!gadget_is_otg(&udc->gadget) && !cpu_is_omap15xx()) {
		u32 l;

		l = omap_readl(OTG_CTRL);
		l |= OTG_BSESSVLD;
		omap_writel(l, OTG_CTRL);
	}
	omap_writew(UDC_DS_CHG_IE, UDC_IRQ_EN);
}