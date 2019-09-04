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
typedef  enum xen_swiotlb_err { ____Placeholder_xen_swiotlb_err } xen_swiotlb_err ;

/* Variables and functions */
#define  XEN_SWIOTLB_EFIXUP 129 
#define  XEN_SWIOTLB_ENOMEM 128 

__attribute__((used)) static const char *xen_swiotlb_error(enum xen_swiotlb_err err)
{
	switch (err) {
	case XEN_SWIOTLB_ENOMEM:
		return "Cannot allocate Xen-SWIOTLB buffer\n";
	case XEN_SWIOTLB_EFIXUP:
		return "Failed to get contiguous memory for DMA from Xen!\n"\
		    "You either: don't have the permissions, do not have"\
		    " enough free memory under 4GB, or the hypervisor memory"\
		    " is too fragmented!";
	default:
		break;
	}
	return "";
}