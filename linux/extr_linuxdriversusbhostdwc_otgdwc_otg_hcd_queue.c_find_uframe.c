#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ speed; } ;
typedef  TYPE_3__ dwc_otg_qh_t ;
struct TYPE_11__ {scalar_t__ port_speed; } ;
struct TYPE_12__ {TYPE_1__ b; } ;
struct TYPE_14__ {TYPE_2__ flags; } ;
typedef  TYPE_4__ dwc_otg_hcd_t ;

/* Variables and functions */
 scalar_t__ DWC_HPRT0_PRTSPD_FULL_SPEED ; 
 scalar_t__ USB_SPEED_HIGH ; 
 int find_multi_uframe (TYPE_4__*,TYPE_3__*) ; 
 int find_single_uframe (TYPE_4__*,TYPE_3__*) ; 

__attribute__((used)) static int find_uframe(dwc_otg_hcd_t * _hcd, dwc_otg_qh_t * _qh)
{
	int ret;
	ret = -1;

	if (_qh->speed == USB_SPEED_HIGH ||
		_hcd->flags.b.port_speed == DWC_HPRT0_PRTSPD_FULL_SPEED) {
		/* if this is a hs transaction we need a full frame - or account for FS usecs */
		ret = find_single_uframe(_hcd, _qh);
	} else {
		/* if this is a fs transaction we may need a sequence of frames */
		ret = find_multi_uframe(_hcd, _qh);
	}
	return ret;
}