#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ port_speed; } ;
struct TYPE_6__ {TYPE_1__ b; } ;
struct TYPE_7__ {int* frame_usecs; TYPE_2__ flags; } ;
typedef  TYPE_3__ dwc_otg_hcd_t ;

/* Variables and functions */
 scalar_t__ DWC_HPRT0_PRTSPD_FULL_SPEED ; 
 int* max_uframe_usecs ; 

void init_hcd_usecs(dwc_otg_hcd_t *_hcd)
{
	int i;
	if (_hcd->flags.b.port_speed == DWC_HPRT0_PRTSPD_FULL_SPEED) {
		_hcd->frame_usecs[0] = 900;
		for (i = 1; i < 8; i++)
			_hcd->frame_usecs[i] = 0;
	} else {
		for (i = 0; i < 8; i++)
			_hcd->frame_usecs[i] = max_uframe_usecs[i];
	}
}