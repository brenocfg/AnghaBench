#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dwc2_qh {int ttport; TYPE_2__* dwc_tt; } ;
struct dwc2_hsotg {int dummy; } ;
struct TYPE_4__ {unsigned long* periodic_bitmaps; TYPE_1__* usb_tt; } ;
struct TYPE_3__ {scalar_t__ multi; } ;

/* Variables and functions */
 int DWC2_ELEMENTS_PER_LS_BITMAP ; 
 scalar_t__ WARN_ON (int) ; 

__attribute__((used)) static unsigned long *dwc2_get_ls_map(struct dwc2_hsotg *hsotg,
				      struct dwc2_qh *qh)
{
	unsigned long *map;

	/* Don't expect to be missing a TT and be doing low speed scheduling */
	if (WARN_ON(!qh->dwc_tt))
		return NULL;

	/* Get the map and adjust if this is a multi_tt hub */
	map = qh->dwc_tt->periodic_bitmaps;
	if (qh->dwc_tt->usb_tt->multi)
		map += DWC2_ELEMENTS_PER_LS_BITMAP * (qh->ttport - 1);

	return map;
}