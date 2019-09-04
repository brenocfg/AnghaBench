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
typedef  unsigned int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  irqs_reconfig; } ;
struct pxa_udc {unsigned int config; TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  UDCCR ; 
 unsigned int UDCCR_AAISN ; 
 unsigned int UDCCR_AAISN_S ; 
 unsigned int UDCCR_ACN ; 
 unsigned int UDCCR_ACN_S ; 
 unsigned int UDCCR_AIN ; 
 unsigned int UDCCR_AIN_S ; 
 int /*<<< orphan*/  UDCCR_SMAC ; 
 int /*<<< orphan*/  UDCISR1 ; 
 int /*<<< orphan*/  UDCISR1_IRCC ; 
 int /*<<< orphan*/  pxa27x_change_configuration (struct pxa_udc*,unsigned int) ; 
 int /*<<< orphan*/  pxa27x_change_interface (struct pxa_udc*,unsigned int,unsigned int) ; 
 unsigned int udc_readl (struct pxa_udc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udc_set_mask_UDCCR (struct pxa_udc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udc_writel (struct pxa_udc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_pxa_ep_matches (struct pxa_udc*) ; 

__attribute__((used)) static void irq_udc_reconfig(struct pxa_udc *udc)
{
	unsigned config, interface, alternate, config_change;
	u32 udccr = udc_readl(udc, UDCCR);

	udc_writel(udc, UDCISR1, UDCISR1_IRCC);
	udc->stats.irqs_reconfig++;

	config = (udccr & UDCCR_ACN) >> UDCCR_ACN_S;
	config_change = (config != udc->config);
	pxa27x_change_configuration(udc, config);

	interface = (udccr & UDCCR_AIN) >> UDCCR_AIN_S;
	alternate = (udccr & UDCCR_AAISN) >> UDCCR_AAISN_S;
	pxa27x_change_interface(udc, interface, alternate);

	if (config_change)
		update_pxa_ep_matches(udc);
	udc_set_mask_UDCCR(udc, UDCCR_SMAC);
}