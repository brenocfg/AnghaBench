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
typedef  int uint16_t ;
struct TYPE_3__ {scalar_t__ dev_speed; int interval; } ;
typedef  TYPE_1__ dwc_otg_qh_t ;

/* Variables and functions */
 scalar_t__ DWC_OTG_EP_SPEED_HIGH ; 

__attribute__((used)) static inline uint16_t frame_incr_val(dwc_otg_qh_t * qh)
{
	return ((qh->dev_speed == DWC_OTG_EP_SPEED_HIGH)
		? ((qh->interval + 8 - 1) / 8)
		: qh->interval);
}