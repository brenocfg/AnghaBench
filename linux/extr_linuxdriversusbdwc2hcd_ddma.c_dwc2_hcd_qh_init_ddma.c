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
struct dwc2_qh {scalar_t__ ep_type; scalar_t__ ntd; scalar_t__ do_split; } ;
struct dwc2_hsotg {int /*<<< orphan*/  frame_list; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HCFG_FRLISTEN_64 ; 
 scalar_t__ USB_ENDPOINT_XFER_INT ; 
 scalar_t__ USB_ENDPOINT_XFER_ISOC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int dwc2_desc_list_alloc (struct dwc2_hsotg*,struct dwc2_qh*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc2_desc_list_free (struct dwc2_hsotg*,struct dwc2_qh*) ; 
 int dwc2_frame_list_alloc (struct dwc2_hsotg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc2_per_sched_enable (struct dwc2_hsotg*,int /*<<< orphan*/ ) ; 

int dwc2_hcd_qh_init_ddma(struct dwc2_hsotg *hsotg, struct dwc2_qh *qh,
			  gfp_t mem_flags)
{
	int retval;

	if (qh->do_split) {
		dev_err(hsotg->dev,
			"SPLIT Transfers are not supported in Descriptor DMA mode.\n");
		retval = -EINVAL;
		goto err0;
	}

	retval = dwc2_desc_list_alloc(hsotg, qh, mem_flags);
	if (retval)
		goto err0;

	if (qh->ep_type == USB_ENDPOINT_XFER_ISOC ||
	    qh->ep_type == USB_ENDPOINT_XFER_INT) {
		if (!hsotg->frame_list) {
			retval = dwc2_frame_list_alloc(hsotg, mem_flags);
			if (retval)
				goto err1;
			/* Enable periodic schedule on first periodic QH */
			dwc2_per_sched_enable(hsotg, HCFG_FRLISTEN_64);
		}
	}

	qh->ntd = 0;
	return 0;

err1:
	dwc2_desc_list_free(hsotg, qh);
err0:
	return retval;
}