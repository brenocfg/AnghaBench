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
typedef  void* u8 ;
struct dwc2_qtd {int /*<<< orphan*/  complete_split; int /*<<< orphan*/  isoc_split_pos; } ;
struct dwc2_hsotg {int dummy; } ;
struct dwc2_host_chan {int do_split; void* hub_port; void* hub_addr; int /*<<< orphan*/  complete_split; int /*<<< orphan*/  xact_pos; } ;
struct dwc2_hcd_urb {int /*<<< orphan*/  priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  dwc2_host_hub_info (struct dwc2_hsotg*,int /*<<< orphan*/ ,int*,int*) ; 

__attribute__((used)) static void dwc2_hc_init_split(struct dwc2_hsotg *hsotg,
			       struct dwc2_host_chan *chan,
			       struct dwc2_qtd *qtd, struct dwc2_hcd_urb *urb)
{
	int hub_addr, hub_port;

	chan->do_split = 1;
	chan->xact_pos = qtd->isoc_split_pos;
	chan->complete_split = qtd->complete_split;
	dwc2_host_hub_info(hsotg, urb->priv, &hub_addr, &hub_port);
	chan->hub_addr = (u8)hub_addr;
	chan->hub_port = (u8)hub_port;
}