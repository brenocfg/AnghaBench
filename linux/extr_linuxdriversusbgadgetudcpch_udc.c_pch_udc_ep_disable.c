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
struct pch_udc_ep {scalar_t__ in; } ;

/* Variables and functions */
 int /*<<< orphan*/  UDC_DESPTR_ADDR ; 
 int /*<<< orphan*/  UDC_EPCTL_ADDR ; 
 int /*<<< orphan*/  UDC_EPCTL_F ; 
 int /*<<< orphan*/  UDC_EPCTL_SNAK ; 
 int /*<<< orphan*/  UDC_EPSTS_ADDR ; 
 int /*<<< orphan*/  UDC_EPSTS_IN ; 
 int /*<<< orphan*/  pch_udc_ep_bit_set (struct pch_udc_ep*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pch_udc_ep_writel (struct pch_udc_ep*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pch_udc_ep_disable(struct pch_udc_ep *ep)
{
	if (ep->in) {
		/* flush the fifo */
		pch_udc_ep_writel(ep, UDC_EPCTL_F, UDC_EPCTL_ADDR);
		/* set NAK */
		pch_udc_ep_writel(ep, UDC_EPCTL_SNAK, UDC_EPCTL_ADDR);
		pch_udc_ep_bit_set(ep, UDC_EPSTS_ADDR, UDC_EPSTS_IN);
	} else {
		/* set NAK */
		pch_udc_ep_writel(ep, UDC_EPCTL_SNAK, UDC_EPCTL_ADDR);
	}
	/* reset desc pointer */
	pch_udc_ep_writel(ep, 0, UDC_DESPTR_ADDR);
}