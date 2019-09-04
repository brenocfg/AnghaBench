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
struct dwc2_hsotg_ep {int /*<<< orphan*/  desc_list_dma; int /*<<< orphan*/  desc_list; } ;
struct dwc2_hsotg {int ep0_state; int /*<<< orphan*/  dev; int /*<<< orphan*/  ctrl_out_desc_dma; int /*<<< orphan*/  ctrl_out_desc; int /*<<< orphan*/  ctrl_in_desc_dma; int /*<<< orphan*/  ctrl_in_desc; int /*<<< orphan*/ * setup_desc_dma; int /*<<< orphan*/ * setup_desc; } ;

/* Variables and functions */
#define  DWC2_EP0_DATA_IN 132 
#define  DWC2_EP0_DATA_OUT 131 
#define  DWC2_EP0_SETUP 130 
#define  DWC2_EP0_STATUS_IN 129 
#define  DWC2_EP0_STATUS_OUT 128 
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int dwc2_gadget_set_ep0_desc_chain(struct dwc2_hsotg *hsotg,
					  struct dwc2_hsotg_ep *hs_ep)
{
	switch (hsotg->ep0_state) {
	case DWC2_EP0_SETUP:
	case DWC2_EP0_STATUS_OUT:
		hs_ep->desc_list = hsotg->setup_desc[0];
		hs_ep->desc_list_dma = hsotg->setup_desc_dma[0];
		break;
	case DWC2_EP0_DATA_IN:
	case DWC2_EP0_STATUS_IN:
		hs_ep->desc_list = hsotg->ctrl_in_desc;
		hs_ep->desc_list_dma = hsotg->ctrl_in_desc_dma;
		break;
	case DWC2_EP0_DATA_OUT:
		hs_ep->desc_list = hsotg->ctrl_out_desc;
		hs_ep->desc_list_dma = hsotg->ctrl_out_desc_dma;
		break;
	default:
		dev_err(hsotg->dev, "invalid EP 0 state in queue %d\n",
			hsotg->ep0_state);
		return -EINVAL;
	}

	return 0;
}