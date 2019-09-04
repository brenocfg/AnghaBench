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
typedef  int u16 ;
struct TYPE_2__ {int b_hnp_enable; int a_hnp_support; int a_alt_hnp_support; } ;
struct omap_udc {TYPE_1__ gadget; } ;

/* Variables and functions */
 int OTG_B_BUSREQ ; 
 int OTG_B_HNPEN ; 
 int /*<<< orphan*/  OTG_CTRL ; 
 int OTG_ID ; 
 int OTG_PULLUP ; 
 int UDC_A_ALT_HNP_SUPPORT ; 
 int UDC_A_HNP_SUPPORT ; 
 int UDC_B_HNP_ENABLE ; 
 int /*<<< orphan*/  UDC_DEVSTAT ; 
 int /*<<< orphan*/  gadget_is_otg (TYPE_1__*) ; 
 int omap_readl (int /*<<< orphan*/ ) ; 
 int omap_readw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void update_otg(struct omap_udc *udc)
{
	u16	devstat;

	if (!gadget_is_otg(&udc->gadget))
		return;

	if (omap_readl(OTG_CTRL) & OTG_ID)
		devstat = omap_readw(UDC_DEVSTAT);
	else
		devstat = 0;

	udc->gadget.b_hnp_enable = !!(devstat & UDC_B_HNP_ENABLE);
	udc->gadget.a_hnp_support = !!(devstat & UDC_A_HNP_SUPPORT);
	udc->gadget.a_alt_hnp_support = !!(devstat & UDC_A_ALT_HNP_SUPPORT);

	/* Enable HNP early, avoiding races on suspend irq path.
	 * ASSUMES OTG state machine B_BUS_REQ input is true.
	 */
	if (udc->gadget.b_hnp_enable) {
		u32 l;

		l = omap_readl(OTG_CTRL);
		l |= OTG_B_HNPEN | OTG_B_BUSREQ;
		l &= ~OTG_PULLUP;
		omap_writel(l, OTG_CTRL);
	}
}