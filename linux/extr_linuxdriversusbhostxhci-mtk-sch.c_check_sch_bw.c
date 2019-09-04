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
typedef  scalar_t__ u32 ;
struct usb_device {scalar_t__ speed; } ;
struct mu3h_sch_ep_info {scalar_t__ esit; scalar_t__ num_budget_microframes; scalar_t__ bw_cost_per_microframe; scalar_t__ offset; } ;
struct mu3h_sch_bw_info {int dummy; } ;

/* Variables and functions */
 int ERANGE ; 
 scalar_t__ HS_BW_BOUNDARY ; 
 scalar_t__ SS_BW_BOUNDARY ; 
 scalar_t__ USB_SPEED_SUPER ; 
 scalar_t__ XHCI_MTK_MAX_ESIT ; 
 scalar_t__ get_max_bw (struct mu3h_sch_bw_info*,struct mu3h_sch_ep_info*,scalar_t__) ; 
 scalar_t__ is_fs_or_ls (scalar_t__) ; 
 int /*<<< orphan*/  update_bus_bw (struct mu3h_sch_bw_info*,struct mu3h_sch_ep_info*,scalar_t__) ; 

__attribute__((used)) static int check_sch_bw(struct usb_device *udev,
	struct mu3h_sch_bw_info *sch_bw, struct mu3h_sch_ep_info *sch_ep)
{
	u32 offset;
	u32 esit;
	u32 num_budget_microframes;
	u32 min_bw;
	u32 min_index;
	u32 worst_bw;
	u32 bw_boundary;

	if (sch_ep->esit > XHCI_MTK_MAX_ESIT)
		sch_ep->esit = XHCI_MTK_MAX_ESIT;

	esit = sch_ep->esit;
	num_budget_microframes = sch_ep->num_budget_microframes;

	/*
	 * Search through all possible schedule microframes.
	 * and find a microframe where its worst bandwidth is minimum.
	 */
	min_bw = ~0;
	min_index = 0;
	for (offset = 0; offset < esit; offset++) {
		if ((offset + num_budget_microframes) > sch_ep->esit)
			break;

		/*
		 * usb_20 spec section11.18:
		 * must never schedule Start-Split in Y6
		 */
		if (is_fs_or_ls(udev->speed) && (offset % 8 == 6))
			continue;

		worst_bw = get_max_bw(sch_bw, sch_ep, offset);
		if (min_bw > worst_bw) {
			min_bw = worst_bw;
			min_index = offset;
		}
		if (min_bw == 0)
			break;
	}
	sch_ep->offset = min_index;

	bw_boundary = (udev->speed == USB_SPEED_SUPER)
				? SS_BW_BOUNDARY : HS_BW_BOUNDARY;

	/* check bandwidth */
	if (min_bw + sch_ep->bw_cost_per_microframe > bw_boundary)
		return -ERANGE;

	/* update bus bandwidth info */
	update_bus_bw(sch_bw, sch_ep, sch_ep->bw_cost_per_microframe);

	return 0;
}