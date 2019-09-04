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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {TYPE_1__* iso_descs; } ;
typedef  TYPE_2__ dwc_otg_hcd_urb_t ;
struct TYPE_4__ {int /*<<< orphan*/  actual_length; } ;

/* Variables and functions */

uint32_t dwc_otg_hcd_urb_get_iso_desc_actual_length(dwc_otg_hcd_urb_t *
						    dwc_otg_urb, int desc_num)
{
	return dwc_otg_urb->iso_descs[desc_num].actual_length;
}