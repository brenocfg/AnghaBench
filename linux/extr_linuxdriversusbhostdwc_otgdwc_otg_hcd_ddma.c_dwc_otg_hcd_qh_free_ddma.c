#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct TYPE_11__ {scalar_t__ ep_type; scalar_t__ channel; } ;
typedef  TYPE_1__ dwc_otg_qh_t ;
struct TYPE_12__ {scalar_t__ frame_list; int /*<<< orphan*/  periodic_channels; } ;
typedef  TYPE_2__ dwc_otg_hcd_t ;

/* Variables and functions */
 scalar_t__ UE_INTERRUPT ; 
 scalar_t__ UE_ISOCHRONOUS ; 
 int /*<<< orphan*/  desc_list_free (struct device*,TYPE_1__*) ; 
 struct device* dwc_otg_hcd_to_dev (TYPE_2__*) ; 
 int /*<<< orphan*/  frame_list_free (TYPE_2__*) ; 
 scalar_t__ microframe_schedule ; 
 int /*<<< orphan*/  per_sched_disable (TYPE_2__*) ; 
 int /*<<< orphan*/  release_channel_ddma (TYPE_2__*,TYPE_1__*) ; 

void dwc_otg_hcd_qh_free_ddma(dwc_otg_hcd_t * hcd, dwc_otg_qh_t * qh)
{
	struct device *dev = dwc_otg_hcd_to_dev(hcd);

	desc_list_free(dev, qh);

	/*
	 * Channel still assigned due to some reasons.
	 * Seen on Isoc URB dequeue. Channel halted but no subsequent
	 * ChHalted interrupt to release the channel. Afterwards
	 * when it comes here from endpoint disable routine
	 * channel remains assigned.
	 */
	if (qh->channel)
		release_channel_ddma(hcd, qh);

	if ((qh->ep_type == UE_ISOCHRONOUS || qh->ep_type == UE_INTERRUPT)
	    && (microframe_schedule || !hcd->periodic_channels) && hcd->frame_list) {

		per_sched_disable(hcd);
		frame_list_free(hcd);
	}
}