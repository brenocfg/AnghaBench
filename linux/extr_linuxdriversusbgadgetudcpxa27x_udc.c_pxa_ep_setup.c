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
struct pxa_ep {int config; int interface; int alternate; int fifo_size; scalar_t__ dir_in; } ;

/* Variables and functions */
 int EPADDR (struct pxa_ep*) ; 
 int EPXFERTYPE (struct pxa_ep*) ; 
 int UDCCONR_AISN ; 
 int UDCCONR_AISN_S ; 
 int UDCCONR_CN ; 
 int UDCCONR_CN_S ; 
 int UDCCONR_ED ; 
 int UDCCONR_EE ; 
 int UDCCONR_EN ; 
 int UDCCONR_EN_S ; 
 int UDCCONR_ET ; 
 int UDCCONR_ET_S ; 
 int UDCCONR_IN ; 
 int UDCCONR_IN_S ; 
 int UDCCONR_MPS ; 
 int UDCCONR_MPS_S ; 
 int /*<<< orphan*/  UDCCR ; 
 int /*<<< orphan*/  udc_ep_writel (struct pxa_ep*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void pxa_ep_setup(struct pxa_ep *ep)
{
	u32 new_udccr;

	new_udccr = ((ep->config << UDCCONR_CN_S) & UDCCONR_CN)
		| ((ep->interface << UDCCONR_IN_S) & UDCCONR_IN)
		| ((ep->alternate << UDCCONR_AISN_S) & UDCCONR_AISN)
		| ((EPADDR(ep) << UDCCONR_EN_S) & UDCCONR_EN)
		| ((EPXFERTYPE(ep) << UDCCONR_ET_S) & UDCCONR_ET)
		| ((ep->dir_in) ? UDCCONR_ED : 0)
		| ((ep->fifo_size << UDCCONR_MPS_S) & UDCCONR_MPS)
		| UDCCONR_EE;

	udc_ep_writel(ep, UDCCR, new_udccr);
}