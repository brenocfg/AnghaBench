#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct dwc2_hcd_urb {TYPE_1__* iso_descs; } ;
struct TYPE_2__ {void* length; void* offset; } ;

/* Variables and functions */

__attribute__((used)) static inline void dwc2_hcd_urb_set_iso_desc_params(
		struct dwc2_hcd_urb *dwc2_urb, int desc_num, u32 offset,
		u32 length)
{
	dwc2_urb->iso_descs[desc_num].offset = offset;
	dwc2_urb->iso_descs[desc_num].length = length;
}