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
struct dwc2_hsotg_ep {scalar_t__ compl_desc; scalar_t__ next_desc; int /*<<< orphan*/  target_frame; int /*<<< orphan*/  dir_in; struct dwc2_hsotg* parent; } ;
struct dwc2_hsotg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TARGET_FRAME_INITIAL ; 
 int /*<<< orphan*/  dwc2_flush_rx_fifo (struct dwc2_hsotg*) ; 
 int /*<<< orphan*/  dwc2_hsotg_complete_request (struct dwc2_hsotg*,struct dwc2_hsotg_ep*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_ep_head (struct dwc2_hsotg_ep*) ; 

__attribute__((used)) static void dwc2_gadget_handle_isoc_bna(struct dwc2_hsotg_ep *hs_ep)
{
	struct dwc2_hsotg *hsotg = hs_ep->parent;

	if (!hs_ep->dir_in)
		dwc2_flush_rx_fifo(hsotg);
	dwc2_hsotg_complete_request(hsotg, hs_ep, get_ep_head(hs_ep), 0);

	hs_ep->target_frame = TARGET_FRAME_INITIAL;
	hs_ep->next_desc = 0;
	hs_ep->compl_desc = 0;
}