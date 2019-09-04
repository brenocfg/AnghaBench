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
struct xhci_ep_ctx {int /*<<< orphan*/  ep_info; int /*<<< orphan*/  ep_info2; } ;
struct usb_device {scalar_t__ speed; } ;
struct mu3h_sch_ep_info {int esit; int cs_count; int num_budget_microframes; int repeat; int pkts; int bw_cost_per_microframe; scalar_t__ burst_mode; scalar_t__ offset; } ;

/* Variables and functions */
 int CTX_TO_EP_INTERVAL (int /*<<< orphan*/ ) ; 
 int CTX_TO_EP_MULT (int /*<<< orphan*/ ) ; 
 int CTX_TO_EP_TYPE (int /*<<< orphan*/ ) ; 
 int CTX_TO_MAX_BURST (int /*<<< orphan*/ ) ; 
 void* DIV_ROUND_UP (int,void*) ; 
 void* FS_PAYLOAD_MAX ; 
 int INT_IN_EP ; 
 int INT_OUT_EP ; 
 int ISOC_IN_EP ; 
 int ISOC_OUT_EP ; 
 int MAX_PACKET_DECODED (int /*<<< orphan*/ ) ; 
 scalar_t__ USB_SPEED_HIGH ; 
 scalar_t__ USB_SPEED_SUPER ; 
 scalar_t__ is_fs_or_ls (scalar_t__) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int roundup_pow_of_two (int) ; 

__attribute__((used)) static void setup_sch_info(struct usb_device *udev,
		struct xhci_ep_ctx *ep_ctx, struct mu3h_sch_ep_info *sch_ep)
{
	u32 ep_type;
	u32 ep_interval;
	u32 max_packet_size;
	u32 max_burst;
	u32 mult;
	u32 esit_pkts;

	ep_type = CTX_TO_EP_TYPE(le32_to_cpu(ep_ctx->ep_info2));
	ep_interval = CTX_TO_EP_INTERVAL(le32_to_cpu(ep_ctx->ep_info));
	max_packet_size = MAX_PACKET_DECODED(le32_to_cpu(ep_ctx->ep_info2));
	max_burst = CTX_TO_MAX_BURST(le32_to_cpu(ep_ctx->ep_info2));
	mult = CTX_TO_EP_MULT(le32_to_cpu(ep_ctx->ep_info));

	sch_ep->esit = 1 << ep_interval;
	sch_ep->offset = 0;
	sch_ep->burst_mode = 0;

	if (udev->speed == USB_SPEED_HIGH) {
		sch_ep->cs_count = 0;

		/*
		 * usb_20 spec section5.9
		 * a single microframe is enough for HS synchromous endpoints
		 * in a interval
		 */
		sch_ep->num_budget_microframes = 1;
		sch_ep->repeat = 0;

		/*
		 * xHCI spec section6.2.3.4
		 * @max_burst is the number of additional transactions
		 * opportunities per microframe
		 */
		sch_ep->pkts = max_burst + 1;
		sch_ep->bw_cost_per_microframe = max_packet_size * sch_ep->pkts;
	} else if (udev->speed == USB_SPEED_SUPER) {
		/* usb3_r1 spec section4.4.7 & 4.4.8 */
		sch_ep->cs_count = 0;
		esit_pkts = (mult + 1) * (max_burst + 1);
		if (ep_type == INT_IN_EP || ep_type == INT_OUT_EP) {
			sch_ep->pkts = esit_pkts;
			sch_ep->num_budget_microframes = 1;
			sch_ep->repeat = 0;
		}

		if (ep_type == ISOC_IN_EP || ep_type == ISOC_OUT_EP) {
			if (esit_pkts <= sch_ep->esit)
				sch_ep->pkts = 1;
			else
				sch_ep->pkts = roundup_pow_of_two(esit_pkts)
					/ sch_ep->esit;

			sch_ep->num_budget_microframes =
				DIV_ROUND_UP(esit_pkts, sch_ep->pkts);

			if (sch_ep->num_budget_microframes > 1)
				sch_ep->repeat = 1;
			else
				sch_ep->repeat = 0;
		}
		sch_ep->bw_cost_per_microframe = max_packet_size * sch_ep->pkts;
	} else if (is_fs_or_ls(udev->speed)) {

		/*
		 * usb_20 spec section11.18.4
		 * assume worst cases
		 */
		sch_ep->repeat = 0;
		sch_ep->pkts = 1; /* at most one packet for each microframe */
		if (ep_type == INT_IN_EP || ep_type == INT_OUT_EP) {
			sch_ep->cs_count = 3; /* at most need 3 CS*/
			/* one for SS and one for budgeted transaction */
			sch_ep->num_budget_microframes = sch_ep->cs_count + 2;
			sch_ep->bw_cost_per_microframe = max_packet_size;
		}
		if (ep_type == ISOC_OUT_EP) {

			/*
			 * the best case FS budget assumes that 188 FS bytes
			 * occur in each microframe
			 */
			sch_ep->num_budget_microframes = DIV_ROUND_UP(
				max_packet_size, FS_PAYLOAD_MAX);
			sch_ep->bw_cost_per_microframe = FS_PAYLOAD_MAX;
			sch_ep->cs_count = sch_ep->num_budget_microframes;
		}
		if (ep_type == ISOC_IN_EP) {
			/* at most need additional two CS. */
			sch_ep->cs_count = DIV_ROUND_UP(
				max_packet_size, FS_PAYLOAD_MAX) + 2;
			sch_ep->num_budget_microframes = sch_ep->cs_count + 2;
			sch_ep->bw_cost_per_microframe = FS_PAYLOAD_MAX;
		}
	}
}