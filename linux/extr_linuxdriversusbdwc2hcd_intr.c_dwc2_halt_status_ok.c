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
struct dwc2_qtd {int dummy; } ;
struct dwc2_hsotg {int dummy; } ;
struct dwc2_host_chan {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static bool dwc2_halt_status_ok(struct dwc2_hsotg *hsotg,
				struct dwc2_host_chan *chan, int chnum,
				struct dwc2_qtd *qtd)
{
#ifdef DEBUG
	u32 hcchar;
	u32 hctsiz;
	u32 hcintmsk;
	u32 hcsplt;

	if (chan->halt_status == DWC2_HC_XFER_NO_HALT_STATUS) {
		/*
		 * This code is here only as a check. This condition should
		 * never happen. Ignore the halt if it does occur.
		 */
		hcchar = dwc2_readl(hsotg, HCCHAR(chnum));
		hctsiz = dwc2_readl(hsotg, HCTSIZ(chnum));
		hcintmsk = dwc2_readl(hsotg, HCINTMSK(chnum));
		hcsplt = dwc2_readl(hsotg, HCSPLT(chnum));
		dev_dbg(hsotg->dev,
			"%s: chan->halt_status DWC2_HC_XFER_NO_HALT_STATUS,\n",
			 __func__);
		dev_dbg(hsotg->dev,
			"channel %d, hcchar 0x%08x, hctsiz 0x%08x,\n",
			chnum, hcchar, hctsiz);
		dev_dbg(hsotg->dev,
			"hcint 0x%08x, hcintmsk 0x%08x, hcsplt 0x%08x,\n",
			chan->hcint, hcintmsk, hcsplt);
		if (qtd)
			dev_dbg(hsotg->dev, "qtd->complete_split %d\n",
				qtd->complete_split);
		dev_warn(hsotg->dev,
			 "%s: no halt status, channel %d, ignoring interrupt\n",
			 __func__, chnum);
		return false;
	}

	/*
	 * This code is here only as a check. hcchar.chdis should never be set
	 * when the halt interrupt occurs. Halt the channel again if it does
	 * occur.
	 */
	hcchar = dwc2_readl(hsotg, HCCHAR(chnum));
	if (hcchar & HCCHAR_CHDIS) {
		dev_warn(hsotg->dev,
			 "%s: hcchar.chdis set unexpectedly, hcchar 0x%08x, trying to halt again\n",
			 __func__, hcchar);
		chan->halt_pending = 0;
		dwc2_halt_channel(hsotg, chan, qtd, chan->halt_status);
		return false;
	}
#endif

	return true;
}