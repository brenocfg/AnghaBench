#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dwc_otg_qh_t ;
typedef  int /*<<< orphan*/  dwc_otg_hcd_urb_t ;
struct TYPE_8__ {TYPE_1__* core_if; } ;
typedef  TYPE_2__ dwc_otg_hcd_t ;
struct TYPE_7__ {scalar_t__ dma_desc_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_ERROR (char*) ; 
 int /*<<< orphan*/ * dwc_otg_hcd_qh_alloc (int) ; 
 int /*<<< orphan*/  dwc_otg_hcd_qh_free (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ dwc_otg_hcd_qh_init_ddma (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qh_init (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

dwc_otg_qh_t *dwc_otg_hcd_qh_create(dwc_otg_hcd_t * hcd,
				    dwc_otg_hcd_urb_t * urb, int atomic_alloc)
{
	dwc_otg_qh_t *qh;

	/* Allocate memory */
	/** @todo add memflags argument */
	qh = dwc_otg_hcd_qh_alloc(atomic_alloc);
	if (qh == NULL) {
		DWC_ERROR("qh allocation failed");
		return NULL;
	}

	qh_init(hcd, qh, urb);

	if (hcd->core_if->dma_desc_enable
	    && (dwc_otg_hcd_qh_init_ddma(hcd, qh) < 0)) {
		dwc_otg_hcd_qh_free(hcd, qh);
		return NULL;
	}

	return qh;
}