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
typedef  unsigned int u32 ;
struct dwc2_hsotg {int dummy; } ;

/* Variables and functions */
 unsigned int DIEPEMPMSK ; 
 unsigned int DIEPINT (unsigned int) ; 
 unsigned int DIEPMSK ; 
 unsigned int DIEPMSK_TXFIFOEMPTY ; 
 unsigned int DOEPINT (unsigned int) ; 
 unsigned int DOEPMSK ; 
 unsigned int DXEPINT_SETUP_RCVD ; 
 unsigned int dwc2_readl (struct dwc2_hsotg*,unsigned int) ; 

__attribute__((used)) static u32 dwc2_gadget_read_ep_interrupts(struct dwc2_hsotg *hsotg,
					  unsigned int idx, int dir_in)
{
	u32 epmsk_reg = dir_in ? DIEPMSK : DOEPMSK;
	u32 epint_reg = dir_in ? DIEPINT(idx) : DOEPINT(idx);
	u32 ints;
	u32 mask;
	u32 diepempmsk;

	mask = dwc2_readl(hsotg, epmsk_reg);
	diepempmsk = dwc2_readl(hsotg, DIEPEMPMSK);
	mask |= ((diepempmsk >> idx) & 0x1) ? DIEPMSK_TXFIFOEMPTY : 0;
	mask |= DXEPINT_SETUP_RCVD;

	ints = dwc2_readl(hsotg, epint_reg);
	ints &= mask;
	return ints;
}