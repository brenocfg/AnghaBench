#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct xhci_virt_ep {scalar_t__ next_frame_id; scalar_t__ use_extended_tbc; struct xhci_ring* ring; } ;
struct xhci_td {int /*<<< orphan*/  start_seg; int /*<<< orphan*/  first_trb; TYPE_5__* last_trb; int /*<<< orphan*/  td_list; } ;
struct xhci_ring {int cycle_state; int /*<<< orphan*/  num_trbs_free_temp; int /*<<< orphan*/  num_trbs_free; int /*<<< orphan*/  enq_seg; TYPE_5__* enqueue; } ;
struct xhci_hcd {int hci_version; int quirks; int /*<<< orphan*/  hcc_params; TYPE_7__** devs; } ;
struct xhci_generic_trb {int dummy; } ;
struct urb_priv {struct xhci_td* td; } ;
struct urb {int number_of_packets; int transfer_flags; int interval; TYPE_2__* dev; int /*<<< orphan*/  stream_id; scalar_t__ start_frame; TYPE_4__* ep; TYPE_3__* iso_frame_desc; struct urb_priv* hcpriv; scalar_t__ transfer_dma; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_14__ {struct xhci_virt_ep* eps; } ;
struct TYPE_8__ {scalar_t__ bandwidth_isoc_reqs; } ;
struct TYPE_13__ {TYPE_1__ self; } ;
struct TYPE_12__ {struct xhci_generic_trb generic; } ;
struct TYPE_11__ {int /*<<< orphan*/  desc; } ;
struct TYPE_10__ {int length; scalar_t__ offset; } ;
struct TYPE_9__ {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (int,unsigned int) ; 
 int EINVAL ; 
 scalar_t__ HCC_CFC (int /*<<< orphan*/ ) ; 
 int TRB_BEI ; 
 int TRB_BUFF_LEN_UP_TO_BOUNDARY (scalar_t__) ; 
 int TRB_CHAIN ; 
 int TRB_FRAME_ID (int) ; 
 int TRB_INTR_TARGET (int /*<<< orphan*/ ) ; 
 int TRB_IOC ; 
 int /*<<< orphan*/  TRB_ISOC ; 
 int TRB_ISP ; 
 int TRB_LEN (int) ; 
 int /*<<< orphan*/  TRB_NORMAL ; 
 int TRB_SIA ; 
 int TRB_TBC (unsigned int) ; 
 int TRB_TD_SIZE (int) ; 
 int TRB_TD_SIZE_TBC (unsigned int) ; 
 int TRB_TLBPC (unsigned int) ; 
 int TRB_TYPE (int /*<<< orphan*/ ) ; 
 int URB_ISO_ASAP ; 
 int XHCI_AMD_PLL_FIX ; 
 int XHCI_AVOID_BEI ; 
 int /*<<< orphan*/  bus_to_hcd (int /*<<< orphan*/ ) ; 
 int count_isoc_trbs_needed (struct urb*,int) ; 
 int /*<<< orphan*/  giveback_first_trb (struct xhci_hcd*,int,unsigned int,int /*<<< orphan*/ ,int,struct xhci_generic_trb*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lower_32_bits (scalar_t__) ; 
 int prepare_transfer (struct xhci_hcd*,TYPE_7__*,unsigned int,int /*<<< orphan*/ ,int,struct urb*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_trb (struct xhci_hcd*,struct xhci_ring*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  td_to_noop (struct xhci_hcd*,struct xhci_ring*,struct xhci_td*,int) ; 
 int /*<<< orphan*/  upper_32_bits (scalar_t__) ; 
 int /*<<< orphan*/  usb_amd_quirk_pll_disable () ; 
 unsigned int usb_endpoint_maxp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_hcd_unlink_urb_from_ep (int /*<<< orphan*/ ,struct urb*) ; 
 scalar_t__ usb_urb_dir_in (struct urb*) ; 
 int /*<<< orphan*/  xhci_dbg (struct xhci_hcd*,char*) ; 
 int /*<<< orphan*/  xhci_err (struct xhci_hcd*,char*) ; 
 unsigned int xhci_get_burst_count (struct xhci_hcd*,struct urb*,unsigned int) ; 
 int xhci_get_isoc_frame_id (struct xhci_hcd*,struct urb*,int) ; 
 unsigned int xhci_get_last_burst_packet_count (struct xhci_hcd*,struct urb*,unsigned int) ; 
 int xhci_td_remainder (struct xhci_hcd*,int,int,int,struct urb*,int) ; 
 TYPE_6__* xhci_to_hcd (struct xhci_hcd*) ; 

__attribute__((used)) static int xhci_queue_isoc_tx(struct xhci_hcd *xhci, gfp_t mem_flags,
		struct urb *urb, int slot_id, unsigned int ep_index)
{
	struct xhci_ring *ep_ring;
	struct urb_priv *urb_priv;
	struct xhci_td *td;
	int num_tds, trbs_per_td;
	struct xhci_generic_trb *start_trb;
	bool first_trb;
	int start_cycle;
	u32 field, length_field;
	int running_total, trb_buff_len, td_len, td_remain_len, ret;
	u64 start_addr, addr;
	int i, j;
	bool more_trbs_coming;
	struct xhci_virt_ep *xep;
	int frame_id;

	xep = &xhci->devs[slot_id]->eps[ep_index];
	ep_ring = xhci->devs[slot_id]->eps[ep_index].ring;

	num_tds = urb->number_of_packets;
	if (num_tds < 1) {
		xhci_dbg(xhci, "Isoc URB with zero packets?\n");
		return -EINVAL;
	}
	start_addr = (u64) urb->transfer_dma;
	start_trb = &ep_ring->enqueue->generic;
	start_cycle = ep_ring->cycle_state;

	urb_priv = urb->hcpriv;
	/* Queue the TRBs for each TD, even if they are zero-length */
	for (i = 0; i < num_tds; i++) {
		unsigned int total_pkt_count, max_pkt;
		unsigned int burst_count, last_burst_pkt_count;
		u32 sia_frame_id;

		first_trb = true;
		running_total = 0;
		addr = start_addr + urb->iso_frame_desc[i].offset;
		td_len = urb->iso_frame_desc[i].length;
		td_remain_len = td_len;
		max_pkt = usb_endpoint_maxp(&urb->ep->desc);
		total_pkt_count = DIV_ROUND_UP(td_len, max_pkt);

		/* A zero-length transfer still involves at least one packet. */
		if (total_pkt_count == 0)
			total_pkt_count++;
		burst_count = xhci_get_burst_count(xhci, urb, total_pkt_count);
		last_burst_pkt_count = xhci_get_last_burst_packet_count(xhci,
							urb, total_pkt_count);

		trbs_per_td = count_isoc_trbs_needed(urb, i);

		ret = prepare_transfer(xhci, xhci->devs[slot_id], ep_index,
				urb->stream_id, trbs_per_td, urb, i, mem_flags);
		if (ret < 0) {
			if (i == 0)
				return ret;
			goto cleanup;
		}
		td = &urb_priv->td[i];

		/* use SIA as default, if frame id is used overwrite it */
		sia_frame_id = TRB_SIA;
		if (!(urb->transfer_flags & URB_ISO_ASAP) &&
		    HCC_CFC(xhci->hcc_params)) {
			frame_id = xhci_get_isoc_frame_id(xhci, urb, i);
			if (frame_id >= 0)
				sia_frame_id = TRB_FRAME_ID(frame_id);
		}
		/*
		 * Set isoc specific data for the first TRB in a TD.
		 * Prevent HW from getting the TRBs by keeping the cycle state
		 * inverted in the first TDs isoc TRB.
		 */
		field = TRB_TYPE(TRB_ISOC) |
			TRB_TLBPC(last_burst_pkt_count) |
			sia_frame_id |
			(i ? ep_ring->cycle_state : !start_cycle);

		/* xhci 1.1 with ETE uses TD_Size field for TBC, old is Rsvdz */
		if (!xep->use_extended_tbc)
			field |= TRB_TBC(burst_count);

		/* fill the rest of the TRB fields, and remaining normal TRBs */
		for (j = 0; j < trbs_per_td; j++) {
			u32 remainder = 0;

			/* only first TRB is isoc, overwrite otherwise */
			if (!first_trb)
				field = TRB_TYPE(TRB_NORMAL) |
					ep_ring->cycle_state;

			/* Only set interrupt on short packet for IN EPs */
			if (usb_urb_dir_in(urb))
				field |= TRB_ISP;

			/* Set the chain bit for all except the last TRB  */
			if (j < trbs_per_td - 1) {
				more_trbs_coming = true;
				field |= TRB_CHAIN;
			} else {
				more_trbs_coming = false;
				td->last_trb = ep_ring->enqueue;
				field |= TRB_IOC;
				/* set BEI, except for the last TD */
				if (xhci->hci_version >= 0x100 &&
				    !(xhci->quirks & XHCI_AVOID_BEI) &&
				    i < num_tds - 1)
					field |= TRB_BEI;
			}
			/* Calculate TRB length */
			trb_buff_len = TRB_BUFF_LEN_UP_TO_BOUNDARY(addr);
			if (trb_buff_len > td_remain_len)
				trb_buff_len = td_remain_len;

			/* Set the TRB length, TD size, & interrupter fields. */
			remainder = xhci_td_remainder(xhci, running_total,
						   trb_buff_len, td_len,
						   urb, more_trbs_coming);

			length_field = TRB_LEN(trb_buff_len) |
				TRB_INTR_TARGET(0);

			/* xhci 1.1 with ETE uses TD Size field for TBC */
			if (first_trb && xep->use_extended_tbc)
				length_field |= TRB_TD_SIZE_TBC(burst_count);
			else
				length_field |= TRB_TD_SIZE(remainder);
			first_trb = false;

			queue_trb(xhci, ep_ring, more_trbs_coming,
				lower_32_bits(addr),
				upper_32_bits(addr),
				length_field,
				field);
			running_total += trb_buff_len;

			addr += trb_buff_len;
			td_remain_len -= trb_buff_len;
		}

		/* Check TD length */
		if (running_total != td_len) {
			xhci_err(xhci, "ISOC TD length unmatch\n");
			ret = -EINVAL;
			goto cleanup;
		}
	}

	/* store the next frame id */
	if (HCC_CFC(xhci->hcc_params))
		xep->next_frame_id = urb->start_frame + num_tds * urb->interval;

	if (xhci_to_hcd(xhci)->self.bandwidth_isoc_reqs == 0) {
		if (xhci->quirks & XHCI_AMD_PLL_FIX)
			usb_amd_quirk_pll_disable();
	}
	xhci_to_hcd(xhci)->self.bandwidth_isoc_reqs++;

	giveback_first_trb(xhci, slot_id, ep_index, urb->stream_id,
			start_cycle, start_trb);
	return 0;
cleanup:
	/* Clean up a partially enqueued isoc transfer. */

	for (i--; i >= 0; i--)
		list_del_init(&urb_priv->td[i].td_list);

	/* Use the first TD as a temporary variable to turn the TDs we've queued
	 * into No-ops with a software-owned cycle bit. That way the hardware
	 * won't accidentally start executing bogus TDs when we partially
	 * overwrite them.  td->first_trb and td->start_seg are already set.
	 */
	urb_priv->td[0].last_trb = ep_ring->enqueue;
	/* Every TRB except the first & last will have its cycle bit flipped. */
	td_to_noop(xhci, ep_ring, &urb_priv->td[0], true);

	/* Reset the ring enqueue back to the first TRB and its cycle bit. */
	ep_ring->enqueue = urb_priv->td[0].first_trb;
	ep_ring->enq_seg = urb_priv->td[0].start_seg;
	ep_ring->cycle_state = start_cycle;
	ep_ring->num_trbs_free = ep_ring->num_trbs_free_temp;
	usb_hcd_unlink_urb_from_ep(bus_to_hcd(urb->dev->bus), urb);
	return ret;
}