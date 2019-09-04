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
struct dwc2_host_chan {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void dwc2_dump_channel_info(struct dwc2_hsotg *hsotg,
				   struct dwc2_host_chan *chan)
{
#ifdef VERBOSE_DEBUG
	int num_channels = hsotg->params.host_channels;
	struct dwc2_qh *qh;
	u32 hcchar;
	u32 hcsplt;
	u32 hctsiz;
	u32 hc_dma;
	int i;

	if (!chan)
		return;

	hcchar = dwc2_readl(hsotg, HCCHAR(chan->hc_num));
	hcsplt = dwc2_readl(hsotg, HCSPLT(chan->hc_num));
	hctsiz = dwc2_readl(hsotg, HCTSIZ(chan->hc_num));
	hc_dma = dwc2_readl(hsotg, HCDMA(chan->hc_num));

	dev_dbg(hsotg->dev, "  Assigned to channel %p:\n", chan);
	dev_dbg(hsotg->dev, "    hcchar 0x%08x, hcsplt 0x%08x\n",
		hcchar, hcsplt);
	dev_dbg(hsotg->dev, "    hctsiz 0x%08x, hc_dma 0x%08x\n",
		hctsiz, hc_dma);
	dev_dbg(hsotg->dev, "    dev_addr: %d, ep_num: %d, ep_is_in: %d\n",
		chan->dev_addr, chan->ep_num, chan->ep_is_in);
	dev_dbg(hsotg->dev, "    ep_type: %d\n", chan->ep_type);
	dev_dbg(hsotg->dev, "    max_packet: %d\n", chan->max_packet);
	dev_dbg(hsotg->dev, "    data_pid_start: %d\n", chan->data_pid_start);
	dev_dbg(hsotg->dev, "    xfer_started: %d\n", chan->xfer_started);
	dev_dbg(hsotg->dev, "    halt_status: %d\n", chan->halt_status);
	dev_dbg(hsotg->dev, "    xfer_buf: %p\n", chan->xfer_buf);
	dev_dbg(hsotg->dev, "    xfer_dma: %08lx\n",
		(unsigned long)chan->xfer_dma);
	dev_dbg(hsotg->dev, "    xfer_len: %d\n", chan->xfer_len);
	dev_dbg(hsotg->dev, "    qh: %p\n", chan->qh);
	dev_dbg(hsotg->dev, "  NP inactive sched:\n");
	list_for_each_entry(qh, &hsotg->non_periodic_sched_inactive,
			    qh_list_entry)
		dev_dbg(hsotg->dev, "    %p\n", qh);
	dev_dbg(hsotg->dev, "  NP waiting sched:\n");
	list_for_each_entry(qh, &hsotg->non_periodic_sched_waiting,
			    qh_list_entry)
		dev_dbg(hsotg->dev, "    %p\n", qh);
	dev_dbg(hsotg->dev, "  NP active sched:\n");
	list_for_each_entry(qh, &hsotg->non_periodic_sched_active,
			    qh_list_entry)
		dev_dbg(hsotg->dev, "    %p\n", qh);
	dev_dbg(hsotg->dev, "  Channels:\n");
	for (i = 0; i < num_channels; i++) {
		struct dwc2_host_chan *chan = hsotg->hc_ptr_array[i];

		dev_dbg(hsotg->dev, "    %2d: %p\n", i, chan);
	}
#endif /* VERBOSE_DEBUG */
}