#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct dwc_otg_hcd_iso_packet_desc {int dummy; } ;
struct TYPE_5__ {int packet_count; } ;
typedef  TYPE_1__ dwc_otg_hcd_urb_t ;
typedef  int /*<<< orphan*/  dwc_otg_hcd_t ;

/* Variables and functions */
 TYPE_1__* DWC_ALLOC (int) ; 
 TYPE_1__* DWC_ALLOC_ATOMIC (int) ; 
 int /*<<< orphan*/  DWC_ERROR (char*,char*,int) ; 

dwc_otg_hcd_urb_t *dwc_otg_hcd_urb_alloc(dwc_otg_hcd_t * hcd,
					 int iso_desc_count, int atomic_alloc)
{
	dwc_otg_hcd_urb_t *dwc_otg_urb;
	uint32_t size;

	size =
	    sizeof(*dwc_otg_urb) +
	    iso_desc_count * sizeof(struct dwc_otg_hcd_iso_packet_desc);
	if (atomic_alloc)
		dwc_otg_urb = DWC_ALLOC_ATOMIC(size);
	else
		dwc_otg_urb = DWC_ALLOC(size);

        if (dwc_otg_urb)
		dwc_otg_urb->packet_count = iso_desc_count;
        else {
		DWC_ERROR("**** DWC OTG HCD URB alloc - "
			"%salloc of %db failed\n",
			atomic_alloc?"atomic ":"", size);
	}
	return dwc_otg_urb;
}