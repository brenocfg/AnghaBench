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
typedef  int /*<<< orphan*/  dwc_otg_qtd_t ;
typedef  int /*<<< orphan*/  dwc_otg_hcd_urb_t ;

/* Variables and functions */
 int /*<<< orphan*/ * dwc_otg_hcd_qtd_alloc (int) ; 
 int /*<<< orphan*/  dwc_otg_hcd_qtd_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

dwc_otg_qtd_t *dwc_otg_hcd_qtd_create(dwc_otg_hcd_urb_t * urb, int atomic_alloc)
{
	dwc_otg_qtd_t *qtd;

	qtd = dwc_otg_hcd_qtd_alloc(atomic_alloc);
	if (qtd == NULL) {
		return NULL;
	}

	dwc_otg_hcd_qtd_init(qtd, urb);
	return qtd;
}