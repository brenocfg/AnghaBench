#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_3__ {int /*<<< orphan*/  pipe_info; } ;
typedef  TYPE_1__ dwc_otg_hcd_urb_t ;

/* Variables and functions */
 int /*<<< orphan*/  dwc_otg_hcd_fill_pipe (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void dwc_otg_hcd_urb_set_pipeinfo(dwc_otg_hcd_urb_t * dwc_otg_urb,
				  uint8_t dev_addr, uint8_t ep_num,
				  uint8_t ep_type, uint8_t ep_dir, uint16_t mps)
{
	dwc_otg_hcd_fill_pipe(&dwc_otg_urb->pipe_info, dev_addr, ep_num,
			      ep_type, ep_dir, mps);
#if 0
	DWC_PRINTF
	    ("addr = %d, ep_num = %d, ep_dir = 0x%x, ep_type = 0x%x, mps = %d\n",
	     dev_addr, ep_num, ep_dir, ep_type, mps);
#endif
}