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
typedef  void* u32 ;
struct dwc3_trb {int ctrl; void* size; int /*<<< orphan*/  bph; int /*<<< orphan*/  bpl; } ;
struct dwc3_ep {size_t trb_enqueue; struct dwc3* dwc; } ;
struct dwc3 {struct dwc3_trb* ep0_trb; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int DWC3_TRB_CTRL_CHN ; 
 int DWC3_TRB_CTRL_HWO ; 
 int DWC3_TRB_CTRL_IOC ; 
 int DWC3_TRB_CTRL_ISP_IMI ; 
 int DWC3_TRB_CTRL_LST ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_dwc3_prepare_trb (struct dwc3_ep*,struct dwc3_trb*) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dwc3_ep0_prepare_one_trb(struct dwc3_ep *dep,
		dma_addr_t buf_dma, u32 len, u32 type, bool chain)
{
	struct dwc3_trb			*trb;
	struct dwc3			*dwc;

	dwc = dep->dwc;
	trb = &dwc->ep0_trb[dep->trb_enqueue];

	if (chain)
		dep->trb_enqueue++;

	trb->bpl = lower_32_bits(buf_dma);
	trb->bph = upper_32_bits(buf_dma);
	trb->size = len;
	trb->ctrl = type;

	trb->ctrl |= (DWC3_TRB_CTRL_HWO
			| DWC3_TRB_CTRL_ISP_IMI);

	if (chain)
		trb->ctrl |= DWC3_TRB_CTRL_CHN;
	else
		trb->ctrl |= (DWC3_TRB_CTRL_IOC
				| DWC3_TRB_CTRL_LST);

	trace_dwc3_prepare_trb(dep, trb);
}