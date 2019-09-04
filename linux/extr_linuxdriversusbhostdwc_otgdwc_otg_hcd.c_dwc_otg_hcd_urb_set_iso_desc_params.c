#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
struct TYPE_5__ {TYPE_1__* iso_descs; } ;
typedef  TYPE_2__ dwc_otg_hcd_urb_t ;
struct TYPE_4__ {void* length; void* offset; } ;

/* Variables and functions */

void dwc_otg_hcd_urb_set_iso_desc_params(dwc_otg_hcd_urb_t * dwc_otg_urb,
					 int desc_num, uint32_t offset,
					 uint32_t length)
{
	dwc_otg_urb->iso_descs[desc_num].offset = offset;
	dwc_otg_urb->iso_descs[desc_num].length = length;
}