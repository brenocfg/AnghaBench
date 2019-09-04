#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dwc2_qtd {int dummy; } ;
struct TYPE_2__ {scalar_t__ host_dma; } ;
struct dwc2_hsotg {TYPE_1__ params; int /*<<< orphan*/  dev; } ;
struct dwc2_host_chan {int /*<<< orphan*/  halt_status; } ;

/* Variables and functions */
 scalar_t__ dbg_hc (struct dwc2_host_chan*) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dwc2_halt_status_ok (struct dwc2_hsotg*,struct dwc2_host_chan*,int,struct dwc2_qtd*) ; 
 int /*<<< orphan*/  dwc2_hc_chhltd_intr_dma (struct dwc2_hsotg*,struct dwc2_host_chan*,int,struct dwc2_qtd*) ; 
 int /*<<< orphan*/  dwc2_release_channel (struct dwc2_hsotg*,struct dwc2_host_chan*,struct dwc2_qtd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dwc2_hc_chhltd_intr(struct dwc2_hsotg *hsotg,
				struct dwc2_host_chan *chan, int chnum,
				struct dwc2_qtd *qtd)
{
	if (dbg_hc(chan))
		dev_vdbg(hsotg->dev, "--Host Channel %d Interrupt: Channel Halted--\n",
			 chnum);

	if (hsotg->params.host_dma) {
		dwc2_hc_chhltd_intr_dma(hsotg, chan, chnum, qtd);
	} else {
		if (!dwc2_halt_status_ok(hsotg, chan, chnum, qtd))
			return;
		dwc2_release_channel(hsotg, chan, qtd, chan->halt_status);
	}
}