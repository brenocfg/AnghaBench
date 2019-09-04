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
typedef  int /*<<< orphan*/  dwc_otg_hcd_t ;

/* Variables and functions */

void dwc_otg_hcd_dump_state(dwc_otg_hcd_t * hcd)
{
#ifdef DEBUG
	int num_channels;
	int i;
	gnptxsts_data_t np_tx_status;
	hptxsts_data_t p_tx_status;

	num_channels = hcd->core_if->core_params->host_channels;
	DWC_PRINTF("\n");
	DWC_PRINTF
	    ("************************************************************\n");
	DWC_PRINTF("HCD State:\n");
	DWC_PRINTF("  Num channels: %d\n", num_channels);
	for (i = 0; i < num_channels; i++) {
		dwc_hc_t *hc = hcd->hc_ptr_array[i];
		DWC_PRINTF("  Channel %d:\n", i);
		DWC_PRINTF("    dev_addr: %d, ep_num: %d, ep_is_in: %d\n",
			   hc->dev_addr, hc->ep_num, hc->ep_is_in);
		DWC_PRINTF("    speed: %d\n", hc->speed);
		DWC_PRINTF("    ep_type: %d\n", hc->ep_type);
		DWC_PRINTF("    max_packet: %d\n", hc->max_packet);
		DWC_PRINTF("    data_pid_start: %d\n", hc->data_pid_start);
		DWC_PRINTF("    multi_count: %d\n", hc->multi_count);
		DWC_PRINTF("    xfer_started: %d\n", hc->xfer_started);
		DWC_PRINTF("    xfer_buff: %p\n", hc->xfer_buff);
		DWC_PRINTF("    xfer_len: %d\n", hc->xfer_len);
		DWC_PRINTF("    xfer_count: %d\n", hc->xfer_count);
		DWC_PRINTF("    halt_on_queue: %d\n", hc->halt_on_queue);
		DWC_PRINTF("    halt_pending: %d\n", hc->halt_pending);
		DWC_PRINTF("    halt_status: %d\n", hc->halt_status);
		DWC_PRINTF("    do_split: %d\n", hc->do_split);
		DWC_PRINTF("    complete_split: %d\n", hc->complete_split);
		DWC_PRINTF("    hub_addr: %d\n", hc->hub_addr);
		DWC_PRINTF("    port_addr: %d\n", hc->port_addr);
		DWC_PRINTF("    xact_pos: %d\n", hc->xact_pos);
		DWC_PRINTF("    requests: %d\n", hc->requests);
		DWC_PRINTF("    qh: %p\n", hc->qh);
		if (hc->xfer_started) {
			hfnum_data_t hfnum;
			hcchar_data_t hcchar;
			hctsiz_data_t hctsiz;
			hcint_data_t hcint;
			hcintmsk_data_t hcintmsk;
			hfnum.d32 =
			    DWC_READ_REG32(&hcd->core_if->
					   host_if->host_global_regs->hfnum);
			hcchar.d32 =
			    DWC_READ_REG32(&hcd->core_if->host_if->
					   hc_regs[i]->hcchar);
			hctsiz.d32 =
			    DWC_READ_REG32(&hcd->core_if->host_if->
					   hc_regs[i]->hctsiz);
			hcint.d32 =
			    DWC_READ_REG32(&hcd->core_if->host_if->
					   hc_regs[i]->hcint);
			hcintmsk.d32 =
			    DWC_READ_REG32(&hcd->core_if->host_if->
					   hc_regs[i]->hcintmsk);
			DWC_PRINTF("    hfnum: 0x%08x\n", hfnum.d32);
			DWC_PRINTF("    hcchar: 0x%08x\n", hcchar.d32);
			DWC_PRINTF("    hctsiz: 0x%08x\n", hctsiz.d32);
			DWC_PRINTF("    hcint: 0x%08x\n", hcint.d32);
			DWC_PRINTF("    hcintmsk: 0x%08x\n", hcintmsk.d32);
		}
		if (hc->xfer_started && hc->qh) {
			dwc_otg_qtd_t *qtd;
			dwc_otg_hcd_urb_t *urb;

			DWC_CIRCLEQ_FOREACH(qtd, &hc->qh->qtd_list, qtd_list_entry) {
				if (!qtd->in_process)
					break;

				urb = qtd->urb;
			DWC_PRINTF("    URB Info:\n");
			DWC_PRINTF("      qtd: %p, urb: %p\n", qtd, urb);
			if (urb) {
				DWC_PRINTF("      Dev: %d, EP: %d %s\n",
					   dwc_otg_hcd_get_dev_addr(&urb->
								    pipe_info),
					   dwc_otg_hcd_get_ep_num(&urb->
								  pipe_info),
					   dwc_otg_hcd_is_pipe_in(&urb->
								  pipe_info) ?
					   "IN" : "OUT");
				DWC_PRINTF("      Max packet size: %d\n",
					   dwc_otg_hcd_get_mps(&urb->
							       pipe_info));
				DWC_PRINTF("      transfer_buffer: %p\n",
					   urb->buf);
				DWC_PRINTF("      transfer_dma: %p\n",
					   (void *)urb->dma);
				DWC_PRINTF("      transfer_buffer_length: %d\n",
					   urb->length);
					DWC_PRINTF("      actual_length: %d\n",
						   urb->actual_length);
				}
			}
		}
	}
	DWC_PRINTF("  non_periodic_channels: %d\n", hcd->non_periodic_channels);
	DWC_PRINTF("  periodic_channels: %d\n", hcd->periodic_channels);
	DWC_PRINTF("  periodic_usecs: %d\n", hcd->periodic_usecs);
	np_tx_status.d32 =
	    DWC_READ_REG32(&hcd->core_if->core_global_regs->gnptxsts);
	DWC_PRINTF("  NP Tx Req Queue Space Avail: %d\n",
		   np_tx_status.b.nptxqspcavail);
	DWC_PRINTF("  NP Tx FIFO Space Avail: %d\n",
		   np_tx_status.b.nptxfspcavail);
	p_tx_status.d32 =
	    DWC_READ_REG32(&hcd->core_if->host_if->host_global_regs->hptxsts);
	DWC_PRINTF("  P Tx Req Queue Space Avail: %d\n",
		   p_tx_status.b.ptxqspcavail);
	DWC_PRINTF("  P Tx FIFO Space Avail: %d\n", p_tx_status.b.ptxfspcavail);
	dwc_otg_hcd_dump_frrem(hcd);
	dwc_otg_dump_global_registers(hcd->core_if);
	dwc_otg_dump_host_registers(hcd->core_if);
	DWC_PRINTF
	    ("************************************************************\n");
	DWC_PRINTF("\n");
#endif
}