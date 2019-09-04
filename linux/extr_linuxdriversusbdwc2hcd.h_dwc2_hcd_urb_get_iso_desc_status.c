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
typedef  int /*<<< orphan*/  u32 ;
struct dwc2_hcd_urb {TYPE_1__* iso_descs; } ;
struct TYPE_2__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */

__attribute__((used)) static inline u32 dwc2_hcd_urb_get_iso_desc_status(
		struct dwc2_hcd_urb *dwc2_urb, int desc_num)
{
	return dwc2_urb->iso_descs[desc_num].status;
}