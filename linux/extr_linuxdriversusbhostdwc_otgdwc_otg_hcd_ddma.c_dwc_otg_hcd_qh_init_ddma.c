#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct TYPE_9__ {scalar_t__ ep_type; scalar_t__ ntd; scalar_t__ do_split; } ;
typedef  TYPE_1__ dwc_otg_qh_t ;
struct TYPE_10__ {int /*<<< orphan*/  frame_list; } ;
typedef  TYPE_2__ dwc_otg_hcd_t ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_ERROR (char*) ; 
 int /*<<< orphan*/  MAX_FRLIST_EN_NUM ; 
 scalar_t__ UE_INTERRUPT ; 
 scalar_t__ UE_ISOCHRONOUS ; 
 int desc_list_alloc (struct device*,TYPE_1__*) ; 
 struct device* dwc_otg_hcd_to_dev (TYPE_2__*) ; 
 int frame_list_alloc (TYPE_2__*) ; 
 int /*<<< orphan*/  per_sched_enable (TYPE_2__*,int /*<<< orphan*/ ) ; 

int dwc_otg_hcd_qh_init_ddma(dwc_otg_hcd_t * hcd, dwc_otg_qh_t * qh)
{
	struct device *dev = dwc_otg_hcd_to_dev(hcd);
	int retval = 0;

	if (qh->do_split) {
		DWC_ERROR("SPLIT Transfers are not supported in Descriptor DMA.\n");
		return -1;
	}

	retval = desc_list_alloc(dev, qh);

	if ((retval == 0)
	    && (qh->ep_type == UE_ISOCHRONOUS || qh->ep_type == UE_INTERRUPT)) {
		if (!hcd->frame_list) {
			retval = frame_list_alloc(hcd);
			/* Enable periodic schedule on first periodic QH */
			if (retval == 0)
				per_sched_enable(hcd, MAX_FRLIST_EN_NUM);
		}
	}

	qh->ntd = 0;

	return retval;
}