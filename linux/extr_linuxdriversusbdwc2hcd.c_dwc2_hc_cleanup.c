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
struct dwc2_hsotg {int dummy; } ;
struct dwc2_host_chan {int /*<<< orphan*/  hc_num; int /*<<< orphan*/  split_order_list_entry; scalar_t__ xfer_started; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCINTMSK (int /*<<< orphan*/ ) ; 
 int HCINTMSK_RESERVED14_31 ; 
 int /*<<< orphan*/  dwc2_writel (struct dwc2_hsotg*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 

void dwc2_hc_cleanup(struct dwc2_hsotg *hsotg, struct dwc2_host_chan *chan)
{
	u32 hcintmsk;

	chan->xfer_started = 0;

	list_del_init(&chan->split_order_list_entry);

	/*
	 * Clear channel interrupt enables and any unhandled channel interrupt
	 * conditions
	 */
	dwc2_writel(hsotg, 0, HCINTMSK(chan->hc_num));
	hcintmsk = 0xffffffff;
	hcintmsk &= ~HCINTMSK_RESERVED14_31;
	dwc2_writel(hsotg, hcintmsk, HCINT(chan->hc_num));
}