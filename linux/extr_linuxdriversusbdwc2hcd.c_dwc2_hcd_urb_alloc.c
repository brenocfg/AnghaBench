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
struct dwc2_hcd_urb {int packet_count; } ;
struct dwc2_hcd_iso_packet_desc {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 struct dwc2_hcd_urb* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dwc2_hcd_urb *dwc2_hcd_urb_alloc(struct dwc2_hsotg *hsotg,
					       int iso_desc_count,
					       gfp_t mem_flags)
{
	struct dwc2_hcd_urb *urb;
	u32 size = sizeof(*urb) + iso_desc_count *
		   sizeof(struct dwc2_hcd_iso_packet_desc);

	urb = kzalloc(size, mem_flags);
	if (urb)
		urb->packet_count = iso_desc_count;
	return urb;
}