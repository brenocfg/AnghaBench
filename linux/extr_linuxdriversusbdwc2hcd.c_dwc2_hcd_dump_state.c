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
struct dwc2_hsotg {int dummy; } ;

/* Variables and functions */

void dwc2_hcd_dump_state(struct dwc2_hsotg *hsotg)
{
#ifdef DEBUG
	struct dwc2_host_chan *chan;
	struct dwc2_hcd_urb *urb;
	struct dwc2_qtd *qtd;
	int num_channels;
	u32 np_tx_status;
	u32 p_tx_status;
	int i;

	num_channels = hsotg->params.host_channels;
	dev_dbg(hsotg->dev, "\n");
	dev_dbg(hsotg->dev,
		"************************************************************\n");
	dev_dbg(hsotg->dev, "HCD State:\n");
	dev_dbg(hsotg->dev, "  Num channels: %d\n", num_channels);

	for (i = 0; i < num_channels; i++) {
		chan = hsotg->hc_ptr_array[i];
		dev_dbg(hsotg->dev, "  Channel %d:\n", i);
		dev_dbg(hsotg->dev,
			"    dev_addr: %d, ep_num: %d, ep_is_in: %d\n",
			chan->dev_addr, chan->ep_num, chan->ep_is_in);
		dev_dbg(hsotg->dev, "    speed: %d\n", chan->speed);
		dev_dbg(hsotg->dev, "    ep_type: %d\n", chan->ep_type);
		dev_dbg(hsotg->dev, "    max_packet: %d\n", chan->max_packet);
		dev_dbg(hsotg->dev, "    data_pid_start: %d\n",
			chan->data_pid_start);
		dev_dbg(hsotg->dev, "    multi_count: %d\n", chan->multi_count);
		dev_dbg(hsotg->dev, "    xfer_started: %d\n",
			chan->xfer_started);
		dev_dbg(hsotg->dev, "    xfer_buf: %p\n", chan->xfer_buf);
		dev_dbg(hsotg->dev, "    xfer_dma: %08lx\n",
			(unsigned long)chan->xfer_dma);
		dev_dbg(hsotg->dev, "    xfer_len: %d\n", chan->xfer_len);
		dev_dbg(hsotg->dev, "    xfer_count: %d\n", chan->xfer_count);
		dev_dbg(hsotg->dev, "    halt_on_queue: %d\n",
			chan->halt_on_queue);
		dev_dbg(hsotg->dev, "    halt_pending: %d\n",
			chan->halt_pending);
		dev_dbg(hsotg->dev, "    halt_status: %d\n", chan->halt_status);
		dev_dbg(hsotg->dev, "    do_split: %d\n", chan->do_split);
		dev_dbg(hsotg->dev, "    complete_split: %d\n",
			chan->complete_split);
		dev_dbg(hsotg->dev, "    hub_addr: %d\n", chan->hub_addr);
		dev_dbg(hsotg->dev, "    hub_port: %d\n", chan->hub_port);
		dev_dbg(hsotg->dev, "    xact_pos: %d\n", chan->xact_pos);
		dev_dbg(hsotg->dev, "    requests: %d\n", chan->requests);
		dev_dbg(hsotg->dev, "    qh: %p\n", chan->qh);

		if (chan->xfer_started) {
			u32 hfnum, hcchar, hctsiz, hcint, hcintmsk;

			hfnum = dwc2_readl(hsotg, HFNUM);
			hcchar = dwc2_readl(hsotg, HCCHAR(i));
			hctsiz = dwc2_readl(hsotg, HCTSIZ(i));
			hcint = dwc2_readl(hsotg, HCINT(i));
			hcintmsk = dwc2_readl(hsotg, HCINTMSK(i));
			dev_dbg(hsotg->dev, "    hfnum: 0x%08x\n", hfnum);
			dev_dbg(hsotg->dev, "    hcchar: 0x%08x\n", hcchar);
			dev_dbg(hsotg->dev, "    hctsiz: 0x%08x\n", hctsiz);
			dev_dbg(hsotg->dev, "    hcint: 0x%08x\n", hcint);
			dev_dbg(hsotg->dev, "    hcintmsk: 0x%08x\n", hcintmsk);
		}

		if (!(chan->xfer_started && chan->qh))
			continue;

		list_for_each_entry(qtd, &chan->qh->qtd_list, qtd_list_entry) {
			if (!qtd->in_process)
				break;
			urb = qtd->urb;
			dev_dbg(hsotg->dev, "    URB Info:\n");
			dev_dbg(hsotg->dev, "      qtd: %p, urb: %p\n",
				qtd, urb);
			if (urb) {
				dev_dbg(hsotg->dev,
					"      Dev: %d, EP: %d %s\n",
					dwc2_hcd_get_dev_addr(&urb->pipe_info),
					dwc2_hcd_get_ep_num(&urb->pipe_info),
					dwc2_hcd_is_pipe_in(&urb->pipe_info) ?
					"IN" : "OUT");
				dev_dbg(hsotg->dev,
					"      Max packet size: %d\n",
					dwc2_hcd_get_mps(&urb->pipe_info));
				dev_dbg(hsotg->dev,
					"      transfer_buffer: %p\n",
					urb->buf);
				dev_dbg(hsotg->dev,
					"      transfer_dma: %08lx\n",
					(unsigned long)urb->dma);
				dev_dbg(hsotg->dev,
					"      transfer_buffer_length: %d\n",
					urb->length);
				dev_dbg(hsotg->dev, "      actual_length: %d\n",
					urb->actual_length);
			}
		}
	}

	dev_dbg(hsotg->dev, "  non_periodic_channels: %d\n",
		hsotg->non_periodic_channels);
	dev_dbg(hsotg->dev, "  periodic_channels: %d\n",
		hsotg->periodic_channels);
	dev_dbg(hsotg->dev, "  periodic_usecs: %d\n", hsotg->periodic_usecs);
	np_tx_status = dwc2_readl(hsotg, GNPTXSTS);
	dev_dbg(hsotg->dev, "  NP Tx Req Queue Space Avail: %d\n",
		(np_tx_status & TXSTS_QSPCAVAIL_MASK) >> TXSTS_QSPCAVAIL_SHIFT);
	dev_dbg(hsotg->dev, "  NP Tx FIFO Space Avail: %d\n",
		(np_tx_status & TXSTS_FSPCAVAIL_MASK) >> TXSTS_FSPCAVAIL_SHIFT);
	p_tx_status = dwc2_readl(hsotg, HPTXSTS);
	dev_dbg(hsotg->dev, "  P Tx Req Queue Space Avail: %d\n",
		(p_tx_status & TXSTS_QSPCAVAIL_MASK) >> TXSTS_QSPCAVAIL_SHIFT);
	dev_dbg(hsotg->dev, "  P Tx FIFO Space Avail: %d\n",
		(p_tx_status & TXSTS_FSPCAVAIL_MASK) >> TXSTS_FSPCAVAIL_SHIFT);
	dwc2_dump_global_registers(hsotg);
	dwc2_dump_host_registers(hsotg);
	dev_dbg(hsotg->dev,
		"************************************************************\n");
	dev_dbg(hsotg->dev, "\n");
#endif
}