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
struct TYPE_3__ {scalar_t__ speed; int multi_count; void* data_pid_start; scalar_t__ ep_is_in; } ;
typedef  TYPE_1__ dwc_hc_t ;

/* Variables and functions */
 scalar_t__ DWC_OTG_EP_SPEED_HIGH ; 
 void* DWC_OTG_HC_PID_DATA0 ; 
 void* DWC_OTG_HC_PID_DATA1 ; 
 void* DWC_OTG_HC_PID_DATA2 ; 
 void* DWC_OTG_HC_PID_MDATA ; 

void set_pid_isoc(dwc_hc_t * hc)
{
	/* Set up the initial PID for the transfer. */
	if (hc->speed == DWC_OTG_EP_SPEED_HIGH) {
		if (hc->ep_is_in) {
			if (hc->multi_count == 1) {
				hc->data_pid_start = DWC_OTG_HC_PID_DATA0;
			} else if (hc->multi_count == 2) {
				hc->data_pid_start = DWC_OTG_HC_PID_DATA1;
			} else {
				hc->data_pid_start = DWC_OTG_HC_PID_DATA2;
			}
		} else {
			if (hc->multi_count == 1) {
				hc->data_pid_start = DWC_OTG_HC_PID_DATA0;
			} else {
				hc->data_pid_start = DWC_OTG_HC_PID_MDATA;
			}
		}
	} else {
		hc->data_pid_start = DWC_OTG_HC_PID_DATA0;
	}
}